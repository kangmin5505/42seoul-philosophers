/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:01:02 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/02 16:06:43 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_all(t_philo_args *philo_args, pthread_t *observer, size_t n_philos)
{
	if (observer != NULL)
		pthread_join(*observer, NULL);
	while (n_philos--)
		pthread_join(philo_args[n_philos].philo, NULL);
}

void	stop_dining(t_shared_args *shared_args)
{
	pthread_mutex_lock(&(shared_args->is_end_lock));
	shared_args->is_end = true;
	pthread_mutex_unlock(&(shared_args->is_end_lock));
}

static bool	dining_error(t_philo_args *philo_args, t_shared_args *shared_args, size_t n_philos)
{
	join_all(philo_args, NULL, n_philos);
	stop_dining(shared_args);
	return (false);
}

bool	start_dining(t_main_args *main_args, t_philo_args *philo_args, t_shared_args *shared_args)
{
	size_t		idx;
	t_timestamp	now;
	pthread_t	observer;

	idx = 0;
	while (idx < main_args->n_philos)
	{
		now = get_timestamp_in_ms();
		philo_args[idx].start_time = now;
		philo_args[idx].last_eat_time = now;
		if (pthread_create(&(philo_args[idx].philo), NULL, philo_routine, &(philo_args[idx])) != 0)
			return (dining_error(philo_args, shared_args, idx - 1));
		idx++;
	}
	if (pthread_create(&observer, NULL, observer_routine, &(t_observer_args){main_args, philo_args, shared_args}) != 0)
		return (dining_error(philo_args, shared_args, idx));
	join_all(philo_args, &observer, idx);
	return (true);
}
