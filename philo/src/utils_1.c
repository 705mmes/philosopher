/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:14:01 by smunio            #+#    #+#             */
/*   Updated: 2023/08/05 14:27:54 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	alone(t_philo *p)
{
	long long	time;

	pthread_mutex_lock(p->state_lock);
	time = get_time() - p->start_time;
	printf("%llu 1 has taken a fork\n", time);
	ft_usleep(p->t_to_die);
	time = get_time() - p->start_time;
	printf("%llu 1 died\n", time);
	pthread_mutex_unlock(p->state_lock);
	exit(EXIT_SUCCESS);
}

void	all_must_die(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->nb_philo)
	{
		pthread_mutex_lock(d->philo[i]->state_lock);
		d->philo[i]->state = 'D';
		pthread_mutex_unlock(d->philo[i]->state_lock);
	}
}

int	is_he_ded(t_data *d)
{
	int			i;
	long long	time;

	i = -1;
	while (++i < d->nb_philo)
	{
		pthread_mutex_lock(d->philo[i]->state_lock);
		if (get_time() > (d->philo[i]->last_meal + d->philo[i]->t_to_die)
			&& (d->philo[i]->state != 'F' && d->philo[i]->state != 'E'))
		{
			pthread_mutex_unlock(d->philo[i]->state_lock);
			all_must_die(d);
			time = get_time() - d->philo[i]->start_time;
			pthread_mutex_lock(d->philo[i]->print_lock);
			printf("%llu %d died\n", time, d->philo[i]->nb);
			pthread_mutex_unlock(d->philo[i]->print_lock);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(d->philo[i]->state_lock);
			return (0);
		}
	}
	return (0);
}

int	is_he_full(t_data *d)
{
	int	i;
	int	how_many_full;

	i = -1;
	how_many_full = 0;
	while (++i < d->nb_philo)
	{
		pthread_mutex_lock(d->philo[i]->state_lock);
		if (d->philo[i]->state == 'F')
		{
			pthread_mutex_unlock(d->philo[i]->state_lock);
			how_many_full++;
		}
		else
			pthread_mutex_unlock(d->philo[i]->state_lock);
	}
	if (how_many_full == d->nb_philo)
		return (1);
	return (0);
}
