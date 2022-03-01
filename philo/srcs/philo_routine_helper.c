/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:38:49 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/01 23:59:32 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_left_fork_first(t_philo_args *arg)
{
	pthread_mutex_lock(arg->left_fork);
	sychronized_status_log(arg, "has taken a fork");
	pthread_mutex_lock(arg->right_fork);
	sychronized_status_log(arg, "has taken a fork");
}

static void	philo_right_fork_first(t_philo_args *arg)
{
	pthread_mutex_lock(arg->right_fork);
	sychronized_status_log(arg, "has taken a fork");
	pthread_mutex_lock(arg->left_fork);
	sychronized_status_log(arg, "has taken a fork");
}

void	philo_release_forks(t_philo_args *arg)
{
	pthread_mutex_unlock(arg->right_fork);
	pthread_mutex_unlock(arg->left_fork);
}

void	philo_take_forks(t_philo_args *arg)
{
	if (arg->id % 2 == 0)
		philo_left_fork_first(arg);
	else
		philo_right_fork_first(arg);
}
