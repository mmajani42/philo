/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:19:40 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/21 22:27:54 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_program(t_data *data)
{
	int	i;

	i = data->args[NB_PH] - 1;
	free(data->args);
	pthread_mutex_destroy(&data->queue);
	pthread_mutex_destroy(&data->die);
	free(data->philo);
	while (i >= 0)
		pthread_mutex_destroy(&data->forks[i--]);
	free(data->forks);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	init_philos(data);
	pthread_mutex_lock(&data->lock);
	data->start = 0;
	if (data->args[NB_PH] == 1)
	{
		pthread_create(&data->philo[0].thread, NULL,
			&routine_one, &data->philo[i]);
		pthread_join(data->philo[0].thread, NULL);
		return (1);
	}
	while (i < data->args[NB_PH])
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
	data->start = 1;
	pthread_mutex_unlock(&data->lock);
	i = 0;
	while (i < data->args[NB_PH])
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(&data) == -1)
		return (-1);
	if (parser_main(&data, ac, av) == -1)
	{
		free(data.args);
		return (-1);
	}
	create_threads(&data);
	free_program(&data);
	return (0);
}
