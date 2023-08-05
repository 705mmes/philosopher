/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatdoido.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:30:29 by smunio            #+#    #+#             */
/*   Updated: 2023/08/05 14:18:17 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take(t_philo *p)
{
	pthread_mutex_lock(p->r_fork);
	msg(FORK, p);
	pthread_mutex_lock(p->l_fork);
	msg(FORK, p);
}

void	drop(t_philo *p)
{
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
	msg(SLEEP, p);
	ft_usleep(p->t_to_sleep);
	msg(THINK, p);
}

void	eat_me(t_philo *p)
{
	take(p);
	pthread_mutex_lock(p->state_lock);
	p->state = 'E';
	pthread_mutex_unlock(p->state_lock);
	pthread_mutex_lock(p->meal_lock);
	p->meals_in_stomach++;
	p->last_meal = get_time();
	pthread_mutex_unlock(p->meal_lock);
	msg(EAT, p);
	ft_usleep(p->t_to_eat);
	drop(p);
}
