/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:11:53 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/23 12:54:44 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h> 
# include <stdbool.h>

# define NB_PH		0
# define T_DIE		1
# define T_EAT		2
# define T_SLEEP	3
# define NB_MEAL	4
# define TAKE		'f'
# define EAT		'e'
# define SLEEP		's'
# define THINK		't'
# define DIE		'd'

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data				*data;
	pthread_t			thread;
	int					id;
	int					meals_taken;
	long				last_meal;
}						t_philo;

typedef struct s_data
{
	t_philo				*philo;
	int					*args;
	pthread_mutex_t		*forks;
	pthread_mutex_t		queue;
	pthread_mutex_t		die;
	pthread_mutex_t		time;
	long				start_time;
	bool				alive;
	int					start;
}						t_data;

//Parsing

int		init_data(t_data *data);
int		init_philos(t_data *data);
int		parser_main(t_data *data, int ac, char **av);

//Threading

int		create_threads(t_data *data);
void	*routine(void *arg);
void	*routine_one(void *arg);
int		is_alive(t_data *data);

//Time

long	timenow(t_data *data);
int		custom_usleep(int time_in_ms, t_philo *philo);

//Utilitaries

int		my_atoi(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *s);
int		ft_isnum(char *str);
int		is_neg(int nb);

#endif