/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:12:19 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/17 15:54:41 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long timeElapsedSinceStart(void)
{
	struct timeval tv;
	static long start_time = 0;

	gettimeofday(&tv, NULL);
	if (start_time == 0)
		start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time);
}

int	custom_usleep(int time_in_ms)
{
	int	start;
	int	now;

	start = timeElapsedSinceStart();
	now = 0;
	while ((now - start) < time_in_ms)
	{
		now = timeElapsedSinceStart();
		usleep(50);
	}
	return (1);
}
