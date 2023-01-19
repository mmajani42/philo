/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:12:28 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/19 17:10:08 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	queued_messages(t_philo *philo, char action)
{
	pthread_mutex_lock(&philo->data->queue);
	if (philo->data->alive == 0)
	{
		pthread_mutex_unlock(&philo->data->queue);
		return (0);
	}
	if (action == TAKE)
		printf("%ld %d has taken a fork\n",
			timenow(), philo->id + 1);
	else if (action == EAT)
		printf("%ld %d is eating\n", timenow(), philo->id + 1);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", timenow(), philo->id + 1);
	else if (action == THINK)
		printf("%ld %d is thinking\n", timenow(), philo->id + 1);
	else if (action == DIE)
	{
		pthread_mutex_lock(&philo->data->die);
		philo->data->alive = 0;
		printf("%ld %d died\n", timenow(), philo->id + 1);
		pthread_mutex_unlock(&philo->data->die);
	}
	pthread_mutex_unlock(&philo->data->queue);
	return (1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	if (philo->id == philo->data->args[NB_PH - 1])
		pthread_mutex_unlock(&philo->data->forks[0]);
	else
		pthread_mutex_unlock(&philo->data->forks[philo->id + 1]);
}

int	take_eat_release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	queued_messages(philo, TAKE);
	if (philo->id == philo->data->args[NB_PH - 1])
		pthread_mutex_lock(&philo->data->forks[0]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->id + 1]);
	queued_messages(philo, TAKE);
	queued_messages(philo, EAT);
	if (custom_usleep(philo->data->args[T_EAT], philo) == -1)
	{
		release_forks(philo);
		return (-1);
	}
	philo->last_meal = timenow();
	philo->meals_taken++;
	release_forks(philo);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
	{
		queued_messages(philo, THINK);
		custom_usleep(philo->data->args[T_EAT], philo);
	}
	while (philo->data->alive == 1 && timenow()
		- philo->last_meal < philo->data->args[T_DIE])
	{
		if (take_eat_release_forks(philo) == -1)
			queued_messages(philo, DIE);
		queued_messages(philo, SLEEP);
		custom_usleep(philo->data->args[T_SLEEP], philo);
		queued_messages(philo, THINK);
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->nb = 0;
	init_philos(data);
	while (i < data->args[NB_PH])
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->args[NB_PH])
		pthread_join(data->philo[i++].thread, NULL);
	return (1);
}
