/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:11:37 by sammeuss          #+#    #+#             */
/*   Updated: 2023/08/08 15:37:18 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philo(t_data	*data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i] = create_philo(i, data);
		if (data->philo[i] == NULL)
		{
			data->error = 1;
			return ;
		}
	}
	i = -1;
	while (++i < data->nb_philo - 1)
		data->philo[i]->r_fork = data->philo[i + 1]->l_fork;
	data->philo[i]->r_fork = data->philo[0]->l_fork;
}

t_philo	*create_philo(int i, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (printf("Malloc Error\n"), NULL);
	philo->nb = i + 1;
	philo->nb_philo = data->nb_philo;
	philo->nb_meals = data->nb_meals;
	philo->meals_in_stomach = 0;
	philo->start_time = data->start_time;
	philo->t_to_die = data->t_to_die;
	philo->t_to_eat = data->t_to_eat;
	philo->t_to_sleep = data->t_to_sleep;
	philo->last_meal = data->start_time;
	philo->data = data;
	philo->meal_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->meal_lock, NULL);
	philo->l_fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->l_fork, NULL);
	philo->print_lock = data->print_lock;
	return (philo);
}

int	check_data(t_data	*data)
{
	if (data->nb_philo > INT32_MAX)
		return (1);
	else if (data->t_to_die > INT32_MAX)
		return (1);
	else if (data->t_to_eat > INT32_MAX)
		return (1);
	else if (data->t_to_sleep > INT32_MAX)
		return (1);
	else if (data->nb_meals > INT32_MAX)
		return (1);
	else
		return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->start_time = get_time();
	data->error = 0;
	data->nb_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	data->is_ded = 0;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	else
		data->nb_meals = -1;
	if (data->nb_philo <= 0 || data->t_to_die <= 0
		|| data->t_to_eat <= 0 || data->t_to_sleep <= 0
		|| check_data(data) == 1)
		return (1);
	data->ded_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->ded_lock, NULL);
	data->print_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->print_lock, NULL);
	data->philo = malloc(sizeof(t_philo *) * data->nb_philo);
	if (!data->philo)
		return (1);
	if (data->nb_philo == 1)
		return (2);
	return (0);
}
