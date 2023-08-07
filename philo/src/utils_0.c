/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:36:09 by sammeuss          #+#    #+#             */
/*   Updated: 2023/08/07 14:30:00 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	int	r;
	int	sign;

	r = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + *str - '0';
		str++;
	}
	return (r * sign);
}

void	ft_usleep(int time)
{
	long long	i;
	long long	target_time;

	i = get_time();
	target_time = i + time;
	while (get_time() < target_time)
		usleep(100);
}

long long	get_time(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, 0);
	return (s_time.tv_sec * 1000 + s_time.tv_usec / 1000);
}

void	msg(char	*msg, t_philo *p)
{
	long long	time;

	pthread_mutex_lock(p->data->ded_lock);
	if (p->data->is_ded != 1)
	{
		pthread_mutex_unlock(p->data->ded_lock);
		pthread_mutex_lock(p->print_lock);
		time = get_time() - p->start_time;
		printf("%llu %d %s\n", time, p->nb, msg);
		pthread_mutex_unlock(p->print_lock);
	}
	else
		pthread_mutex_unlock(p->data->ded_lock);
}
