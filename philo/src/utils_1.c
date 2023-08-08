/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:14:01 by smunio            #+#    #+#             */
/*   Updated: 2023/08/08 12:47:55 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	alone(t_philo *p)
{
	long long	time;

	pthread_mutex_lock(p->print_lock);
	time = get_time() - p->start_time;
	printf("%llu 1 has taken a fork\n", time);
	ft_usleep(p->t_to_die);
	time = get_time() - p->start_time;
	printf("%llu 1 died\n", time);
	exit(EXIT_SUCCESS);
}

void	all_must_die(t_data *d)
{
	pthread_mutex_lock(d->ded_lock);
	d->is_ded = 1;
	pthread_mutex_unlock(d->ded_lock);
}

int	is_he_ded(t_data *d)
{
	int			i;
	long long	time;

	i = -1;
	while (++i < d->nb_philo)
	{
		pthread_mutex_lock(d->philo[i]->meal_lock);
		if (get_time() > (d->philo[i]->last_meal + d->philo[i]->t_to_die))
		{
			pthread_mutex_unlock(d->philo[i]->meal_lock);
			all_must_die(d);
			pthread_mutex_lock(d->philo[i]->print_lock);
			time = get_time() - d->philo[i]->start_time;
			printf("%llu %d died\n", time, d->philo[i]->nb);
			pthread_mutex_unlock(d->philo[i]->print_lock);
			return (1);
		}
		pthread_mutex_unlock(d->philo[i]->meal_lock);
	}
	return (0);
}

int	full_utils(t_data *d)
{
	int	how_many_full;
	int	i;

	i = -1;
	how_many_full = 0;
	while (++i < d->nb_philo)
	{
		pthread_mutex_lock(d->philo[i]->meal_lock);
		if (d->philo[i]->meals_in_stomach == d->nb_meals)
		{
			how_many_full++;
			pthread_mutex_unlock(d->philo[i]->meal_lock);
		}
		pthread_mutex_unlock(d->philo[i]->meal_lock);
	}
	return (how_many_full);
}

int	is_he_full(t_data *d)
{
	int	i;
	int	how_many_full;

	i = -1;
	how_many_full = 0;
	while (++i < d->nb_philo)
	{
		how_many_full = full_utils(d);
		pthread_mutex_lock(d->philo[i]->meal_lock);
		if (how_many_full == d->nb_philo)
		{
			pthread_mutex_unlock(d->philo[i]->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(d->philo[i]->meal_lock);
	}
	return (0);
}
