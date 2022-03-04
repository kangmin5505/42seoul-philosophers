/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:40:42 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/03 17:44:57 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_release_forks(t_shared_args *args)
{
	sem_post(args->forks);
	sem_post(args->forks);
	sem_post(args->forks_pair);
}

void	philo_takes_forks(t_philo_args *philo_args, t_shared_args *shared_args)
{
	sem_wait(shared_args->forks_pair);
	sem_wait(shared_args->forks);
	synchronized_status_log(philo_args, shared_args, "has taken a fork");
	sem_wait(shared_args->forks);
	synchronized_status_log(philo_args, shared_args, "has taken a fork");
}
