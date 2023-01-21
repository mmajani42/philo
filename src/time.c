/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:12:19 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/21 18:02:00 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	timenow(void)
{
	struct timeval	tv;
	static long		start_time = 0;

	gettimeofday(&tv, NULL);
	if (start_time == 0)
		start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
}

int	custom_usleep(int time_in_ms, t_philo *philo)
{
	long	start;
	long	now;

	start = timenow();
	now = 0;
	while ((now - start) < time_in_ms)
	{
		if (now - philo->last_meal >= philo->data->args[T_DIE])
			return (-1);
		now = timenow();
		usleep(50);
	}
	return (1);
}
