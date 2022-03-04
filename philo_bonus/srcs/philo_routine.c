/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:57:56 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/04 08:57:02 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eating_philo(t_main_args *main_args, t_philo_args *philo_args, \
						 t_shared_args *shared_args)
{
	philo_takes_forks(philo_args, shared_args);
	sem_wait(philo_args->event_lock);
	philo_args->last_eat_time = get_timestamp_in_ms();
	sem_post(philo_args->event_lock);
	synchronized_status_log(philo_args, shared_args, "is eating");
	smart_sleep(main_args->time_eat);
	sem_wait(philo_args->event_lock);
	if (++(philo_args->n_eat) == main_args->n_must_eat)
		sem_post(shared_args->full_philos);
	sem_post(philo_args->event_lock);
	philo_release_forks(shared_args);
}

static void	sleeping_philo(t_main_args *main_args, t_philo_args *philo_args, \
						   t_shared_args *shared_args)
{
	synchronized_status_log(philo_args, shared_args, "is sleeping");
	smart_sleep(main_args->time_sleep);
}

static void	thinking_philo(t_philo_args *philo_args, t_shared_args *shared_args)
{
	synchronized_status_log(philo_args, shared_args, "is thinking");
	usleep(EPSILON);
}

int	philo_routine(t_main_args *main_args, t_philo_args *philo_args, \
				  t_shared_args *shared_args)
{
	pthread_t	self_dead_observer;
	char		name[20];

	set_sem_name(name, philo_args->id);
	if (open_semaphore(name, 1, &(philo_args->event_lock)) == false)
		return (false);
	if (pthread_create(&self_dead_observer, NULL, check_self_dead, \
					   &(t_self_dead_args){main_args, shared_args, philo_args}))
		return (1);
	while (1)
	{
		eating_philo(main_args, philo_args, shared_args);
		sleeping_philo(main_args, philo_args, shared_args);
		thinking_philo(philo_args, shared_args);
	}
}
