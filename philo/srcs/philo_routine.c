/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:57:03 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/02 14:11:05 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dining_end(t_philo_args *arg)
{
	bool	result;

	pthread_mutex_lock(arg->is_end_lock);
	result = *(arg->is_end);
	pthread_mutex_unlock(arg->is_end_lock);
	return (result);
}

static bool	eating_philo(t_philo_args *arg)
{
	philo_take_forks(arg);
	pthread_mutex_lock(&(arg->event_lock));
	arg->last_eat_time = get_timestamp_in_ms();
	pthread_mutex_unlock(&(arg->event_lock));
	synchronized_status_log(arg, "is eating");
	smart_sleep(arg->time_eat);
	pthread_mutex_lock(&(arg->event_lock));
	arg->n_eat++;
	pthread_mutex_unlock(&(arg->event_lock));
	philo_release_forks(arg);
	return (is_dining_end(arg));
}

static bool	sleeping_philo(t_philo_args *arg)
{
	synchronized_status_log(arg, "is sleeping");
	smart_sleep(arg->time_sleep);
	return (is_dining_end(arg));
}

static bool	thinking_philo(t_philo_args *arg)
{
	synchronized_status_log(arg, "is thinking");
	usleep(EPSILON);
	return (is_dining_end(arg));
}

void	*philo_routine(void	*_arg)
{
	t_philo_args	*arg;

	arg = (t_philo_args *)_arg;
	if (arg->id % 2 == 0)
		usleep(EPSILON);
	while (1)
	{
		if (eating_philo(arg) == true)
			return (NULL);
		if (sleeping_philo(arg) == true)
			return (NULL);
		if (thinking_philo(arg) == true)
			return (NULL);
	}
}
