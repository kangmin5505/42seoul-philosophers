/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:07:29 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/02 00:51:20 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	someone_dead_handler(t_philo_args *arg)
{
	pthread_mutex_lock(arg->is_end_lock);
	sychronized_status_log(arg, "died");
	*(arg->is_end) = true;
	pthread_mutex_unlock(arg->is_end_lock);
}

bool	catch_end_status(t_observer_args *arg)
{
	size_t	idx;
	bool	is_dead;
	bool	everyone_full;

	idx = 0;
	is_dead = false;
	everyone_full = arg->main_args->optional_arg;
	while (idx < arg->main_args->n_philos)
	{
		pthread_mutex_lock(&(arg->philo_args[idx].event_lock));
		everyone_full &= (arg->philo_args[idx].n_eat >= arg->main_args->n_must_eat);
		is_dead |= (get_timestamp_in_ms() - arg->philo_args[idx].last_eat_time > arg->main_args->time_die);
		pthread_mutex_unlock(&(arg->philo_args[idx].event_lock));
		if (is_dead != false)
			break ;
		idx++;
	}
	if (is_dead != false)
		someone_dead_handler(arg->philo_args + idx);
	return (is_dead || everyone_full);
}

void	*observer_routine(void *_arg)
{
	t_observer_args	*arg;

	arg = (t_observer_args *)_arg;
	while (1)
	{
		if (catch_end_status(arg) == true)
		{
			stop_dining(arg->shared_args);
			return (NULL);
		}
	}
}
