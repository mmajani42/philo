/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:12:10 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/19 15:57:16 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->alive = 1;
	data->philo = malloc(sizeof(t_philo) * data->args[NB_PH]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->args[NB_PH]);
	while (i < data->args[NB_PH])
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philo[i].id = i;
		data->philo[i].meals_taken = 0;
		data->philo[i].last_meal = 0;
		data->philo[i++].data = data;
	}
}

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->args = malloc(sizeof(int) * 5);
	while (i < 5)
		data->args[i++] = 0;
	pthread_mutex_init(&data->queue, NULL);
	pthread_mutex_init(&data->die, NULL);
}
