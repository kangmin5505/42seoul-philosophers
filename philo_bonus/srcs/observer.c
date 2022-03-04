/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:57:46 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/04 08:55:24 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*observer_routine(void *_args)
{
	t_observer_args	*args;
	size_t			id;

	args = (t_observer_args *)_args;
	id = 0;
	while (id < args->n_philos)
	{
		sem_wait(args->full_philos);
		id++;
	}
	kill(args->last_philo, SIGTERM);
	return (NULL);
}

static int	is_philo_dead(t_self_dead_args *args)
{
	int	is_dead;

	is_dead = (get_timestamp_in_ms() - args->philo_args->last_eat_time \
			   > args->main_args->time_die);
	if (is_dead)
	{
		sem_wait(args->shared_args->is_end_lock);
		printf("%zu %zu died\n", get_timestamp_in_ms() - \
			   args->philo_args->start_time, args->philo_args->id);
	}
	return (is_dead);
}

void	*check_self_dead(void *_args)
{
	t_self_dead_args	*args;

	args = (t_self_dead_args *)_args;
	while (1)
	{
		sem_wait(args->philo_args->event_lock);
		if (is_philo_dead(args))
			exit(0);
		sem_post(args->philo_args->event_lock);
		usleep(EPSILON);
	}
}
