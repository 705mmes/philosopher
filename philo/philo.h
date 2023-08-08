/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:29:51 by sammeuss          #+#    #+#             */
/*   Updated: 2023/08/08 16:36:50 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/time.h>
# include <limits.h>
# include <fcntl.h>
# include <pthread.h>

# define FORK		"has taken a fork"
# define THINK		"is thinking"
# define SLEEP		"is sleeping"
# define EAT		"is eating"
# define IS_DEAD	"died"	

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				nb;
	int				nb_philo;
	int				nb_meals;
	int				meals_in_stomach;
	long long		last_meal;
	long long		start_time;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	t_data			*data;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*print_lock;
	pthread_t		thread;
}		t_philo;

typedef struct s_data
{
	int				is_ded;
	int				nb_meals;
	int				error;
	int				nb_philo;
	long long		start_time;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	pthread_mutex_t	*ded_lock;
	pthread_mutex_t	*print_lock;
	pthread_t		main_thread;
	t_philo			**philo;
}		t_data;

// -> utils_0.c

int			ft_is_digit(char c);
long		ft_atoi(char *str);
void		ft_usleep(int time);
long long	get_time(void);
void		msg(char	*msg, t_philo *p);

// -> utils_1.c

void		alone(t_philo *p);
int			is_he_ded(t_data *d);
int			is_he_full(t_data *d);
int			full_utils(t_data *d);
void		all_must_die(t_data *d);

// -> parsing.c

int			check_args(char **s);

// -> whatdoido.c

void		drop(t_philo *p);
void		take(t_philo *p);
void		eat_me(t_philo *p);

// -> main.c

void		free_all(t_data *d);

// -> runnin.c

void		first_part(t_philo *p);
void		*routine(void *philo);
void		run(t_data *data);
void		im_the_boss(void	*philo);

// -> data_init.c

int			check_data(t_data	*data);
void		init_philo(t_data *data);
int			init_data(t_data	*data, int argc, char	**argv);
t_philo		*create_philo(int i, t_data *data);

#endif