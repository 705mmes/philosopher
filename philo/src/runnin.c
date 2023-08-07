/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runnin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:11:11 by sammeuss          #+#    #+#             */
/*   Updated: 2023/08/07 16:16:35 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	im_the_boss(void	*data)
{
	t_data		*d;

	d = (t_data *)data;
	ft_usleep(10);
	while (1)
	{
		if (is_he_ded(d) == 1)
			break ;
		if (is_he_full(d) == 1)
			break ;
	}
}

void	run(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb_philo)
	{
		pthread_create(&(d)->philo[i]->thread, NULL,
			(void *)routine, (void *)d->philo[i]);
		i += 2;
	}
	i = 1;
	while (i < d->nb_philo)
	{
		pthread_create(&(d)->philo[i]->thread, NULL,
			(void *)routine, (void *)d->philo[i]);
		i += 2;
	}
	i = -1;
	pthread_create(&(d)->main_thread, NULL,
		(void *)im_the_boss, (void *)d);
	while (++i < d->nb_philo)
		pthread_join(d->philo[i]->thread, NULL);
	pthread_join(d->main_thread, NULL);
}

void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->nb % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (p->nb_philo == 1)
			alone(p);
		eat_me(p);
		if (p->nb_philo > 1)
		{
			pthread_mutex_lock(p->data->ded_lock);
			pthread_mutex_lock(p->meal_lock);
			if (p->data->is_ded == 1 || (p->meals_in_stomach == p->nb_meals))
			{
				pthread_mutex_unlock(p->data->ded_lock);
				pthread_mutex_unlock(p->meal_lock);
				break ;
			}
			pthread_mutex_unlock(p->meal_lock);
			pthread_mutex_unlock(p->data->ded_lock);
		}
	}
	return (NULL);
}
