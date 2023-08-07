/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:50:32 by sammeuss          #+#    #+#             */
/*   Updated: 2023/08/07 15:03:17 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_data *d)
{
	int i;

	i = 0;
	pthread_mutex_destroy(d->ded_lock);
	pthread_mutex_destroy(d->print_lock);
	while (i < d->nb_philo)
	{
		pthread_mutex_destroy(d->philo[i]->l_fork);
		pthread_mutex_destroy(d->philo[i]->meal_lock);
		i++;
	}
	free(d->philo);
}

int	main(int argc, char **argv)
{	
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Error\nWrong amount of args\n"));
	if (check_args(argv))
		return (printf("Error\nWrong args\n"));
	if (init_data(&data, argc, argv) == 2)
		data.philo[0] = create_philo(0, &data);
	else if (init_data(&data, argc, argv) == 1)
		return (printf("Error\nSomething's wrong\n"));
	init_philo(&data);
	if (data.error == 1)
		return (1);
	run(&data);
	free_all(&data);
	return (0);
}
 