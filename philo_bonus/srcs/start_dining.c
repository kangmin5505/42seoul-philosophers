/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dining.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:55:52 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/04 09:25:45 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	set_philo_arg(t_philo_args *philo_args, size_t id)
{
	t_timestamp	now;

	now = get_timestamp_in_ms();
	philo_args->id = id;
	philo_args->n_eat = 0;
	philo_args->start_time = now;
	philo_args->last_eat_time = now;
}

static bool	free_and_return(pid_t *pids, bool result)
{
	free(pids);
	return (result);
}

static bool	wait_end(pthread_t observer, t_main_args *main_args, \
					 t_shared_args *shared_args, pid_t *pids)
{
	int		status;
	bool	result;
	size_t	id;

	waitpid(-1, &status, 0);
	result = (WEXITSTATUS(status) == 0 || WEXITSTATUS(status) == SIGTERM);
	id = 0;
	while (id < main_args->n_philos)
	{
		if (!kill(pids[id], SIGTERM))
			waitpid(pids[id], &status, 0);
		id++;
	}
	while (id--)
		sem_post(shared_args->full_philos);
	if (main_args->optional_arg == true)
		pthread_join(observer, NULL);
	return (result);
}

static int	run_observer(t_observer_args *args, pthread_t *observer)
{
	if (pthread_create(observer, NULL, observer_routine, args) != 0)
		return (1);
	return (0);
}

bool	start_dining(t_main_args *main_args, t_philo_args *philo_args, \
					 t_shared_args *shared_args)
{
	pid_t		*pids;
	size_t		id;
	bool		result;
	pthread_t	observer;

	pids = (pid_t *)malloc(sizeof(pid_t) * main_args->n_philos);
	if (pids == NULL)
		return (false);
	id = 0;
	while (id < main_args->n_philos)
	{
		set_philo_arg(philo_args, id + 1);
		pids[id] = fork();
		if (pids[id] < 0)
			return (free_and_return(pids, false));
		else if (pids[id++] == 0)
			exit(philo_routine(main_args, philo_args, shared_args));
	}
	observer = NULL;
	if (main_args->optional_arg == true)
		if (run_observer(&(t_observer_args){main_args->n_philos, pids[id - 1], \
						 shared_args->full_philos}, &observer))
			return (free_and_return(pids, false));
	result = wait_end(observer, main_args, shared_args, pids);
	return (free_and_return(pids, result));
}
