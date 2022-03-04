/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:55:51 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/04 08:38:43 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	mutex_init_fork_event(pthread_mutex_t *_fork, \
								  pthread_mutex_t *event_lock)
{
	if (pthread_mutex_init(_fork, NULL) != 0)
		return (false);
	if (pthread_mutex_init(event_lock, NULL) != 0)
	{
		pthread_mutex_destroy(_fork);
		return (false);
	}
	return (true);
}

bool	init_mutex(size_t n_philos, t_philo_args *philo_args, \
				   t_shared_args *shared_args)
{
	size_t	idx;

	if (pthread_mutex_init(&(shared_args->is_end_lock), NULL) != 0)
		return (false);
	idx = 0;
	while (idx < n_philos)
	{
		if (mutex_init_fork_event(&(philo_args[idx]._fork), \
								  &(philo_args[idx].event_lock)) == false)
		{
			while (--idx)
			{
				pthread_mutex_destroy(&(philo_args[idx]._fork));
				pthread_mutex_destroy(&(philo_args[idx].event_lock));
			}
			pthread_mutex_destroy(&(shared_args->is_end_lock));
			return (false);
		}
		idx++;
	}
	return (true);
}

void	destroy_mutex(size_t n_philos, t_philo_args *philo_args, \
					  t_shared_args *shared_args)
{
	size_t	idx;

	pthread_mutex_destroy(&(shared_args->is_end_lock));
	idx = 0;
	while (idx < n_philos)
	{
		pthread_mutex_destroy(&(philo_args->_fork));
		pthread_mutex_destroy(&(philo_args->event_lock));
		idx++;
	}
}
