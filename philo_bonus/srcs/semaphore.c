/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:30:54 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/04 08:56:38 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	close_semaphore(t_shared_args *shared_args)
{
	sem_close(shared_args->forks);
	sem_close(shared_args->forks_pair);
	sem_close(shared_args->full_philos);
	sem_close(shared_args->is_end_lock);
}

static void	unlink_semaphore(void)
{
	sem_unlink(SEM_NAME_FORKS);
	sem_unlink(SEM_NAME_FORKS_PAIR);
	sem_unlink(SEM_NAME_FULL_PHILOS);
	sem_unlink(SEM_NAME_IS_END_LOCK);
}

void	destroy_semaphore(t_shared_args *shared_args)
{
	close_semaphore(shared_args);
	unlink_semaphore();
}

bool	open_semaphore(const char *name, unsigned int value, sem_t **target)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, value);
	if (sem == SEM_FAILED)
		return (false);
	*target = sem;
	return (true);
}

bool	init_semaphore(t_shared_args *shared_args, size_t n_philos)
{
	bool	is_success;

	memset(shared_args, 0, sizeof(t_shared_args));
	is_success = true;
	is_success |= open_semaphore(SEM_NAME_FORKS, n_philos, \
								 &(shared_args->forks));
	is_success |= open_semaphore(SEM_NAME_FORKS_PAIR, n_philos / 2, \
								 &(shared_args->forks_pair));
	is_success |= open_semaphore(SEM_NAME_FULL_PHILOS, 0, \
								 &(shared_args->full_philos));
	is_success |= open_semaphore(SEM_NAME_IS_END_LOCK, 1, \
								 &(shared_args->is_end_lock));
	if (is_success == false)
		destroy_semaphore(shared_args);
	return (is_success);
}
