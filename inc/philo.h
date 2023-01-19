/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:11:53 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/19 16:54:49 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h> 

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
	int					nb;
	pthread_mutex_t		*forks;
	pthread_mutex_t		queue;
	pthread_mutex_t		die;
	int					alive;
}						t_data;

//Parsing

void	init_data(t_data *data);
void	init_philos(t_data *data);
int		parser_main(t_data *data, int ac, char **av);

//Threading

int		create_threads(t_data *data);

//Time

long	timenow(void);
int		custom_usleep(int time_in_ms, t_philo *philo);

//Utilitaries

int		my_atoi(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *s);
int		ft_isnum(char *str);
int		is_neg(int nb);

#endif