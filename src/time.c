/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:12:19 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/21 19:25:29 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	timenow(t_data *data)
{
	struct timeval	tv;

	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_lock(&data->time);
	gettimeofday(&tv, NULL);
	if (data->start_time == 0)
		data->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_unlock(&data->time);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - data->start_time);
}

int	custom_usleep(int time_in_ms, t_philo *philo)
{
	long	start;
	long	now;

	start = timenow(philo->data);
	now = 0;
	while ((now - start) < time_in_ms)
	{
		if (now - philo->last_meal >= philo->data->args[T_DIE])
			return (-1);
		now = timenow(philo->data);
		usleep(50);
	}
	return (1);
}
