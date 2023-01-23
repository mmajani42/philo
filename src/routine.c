/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:12:28 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/23 12:52:27 by mmajani          ###   ########lyon.fr   */
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
			timenow(philo->data), philo->id + 1);
	else if (action == EAT)
		printf("%ld %d is eating\n", timenow(philo->data), philo->id + 1);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", timenow(philo->data), philo->id + 1);
	else if (action == THINK)
		printf("%ld %d is thinking\n", timenow(philo->data), philo->id + 1);
	else if (action == DIE)
	{
		pthread_mutex_lock(&philo->data->die);
		philo->data->alive = 0;
		printf("%ld %d died\n", timenow(philo->data), philo->id + 1);
		pthread_mutex_unlock(&philo->data->die);
	}
	pthread_mutex_unlock(&philo->data->queue);
	return (1);
}

void	release_forks(t_philo *philo)
{	
	if (philo->id == philo->data->args[NB_PH] - 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
		pthread_mutex_unlock(&philo->data->forks[0]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->id]);
		pthread_mutex_unlock(&philo->data->forks[philo->id + 1]);
	}
}

int	take_eat_release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	queued_messages(philo, TAKE);
	if (philo->id == philo->data->args[NB_PH] - 1)
	{
		pthread_mutex_lock(&philo->data->forks[0]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->id + 1]);
	}
	queued_messages(philo, TAKE);
	queued_messages(philo, EAT);
	if (custom_usleep(philo->data->args[T_EAT], philo) == -1)
	{
		release_forks(philo);
		return (-1);
	}
	philo->last_meal = timenow(philo->data);
	philo->meals_taken++;
	release_forks(philo);
	return (1);
}

void	*routine_one(void *arg)
{
	t_philo	*philo;

	philo = arg;
	queued_messages(philo, TAKE);
	custom_usleep(philo->data->args[T_DIE], philo);
	queued_messages(philo, DIE);
	return (0);
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
	while (is_alive(philo->data) == 1 && timenow(philo->data)
		- philo->last_meal < philo->data->args[T_DIE])
	{
		if (take_eat_release_forks(philo) == -1)
			queued_messages(philo, DIE);
		if (philo->data->args[NB_MEAL]
			&& philo->meals_taken >= philo->data->args[NB_MEAL] + 1)
			return (0);
		queued_messages(philo, SLEEP);
		custom_usleep(philo->data->args[T_SLEEP], philo);
		queued_messages(philo, THINK);
	}
	return (0);
}
