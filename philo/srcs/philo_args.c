/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:41:10 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/04 08:37:51 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	alloc_philo_args(size_t n_philos, t_philo_args **philo_args)
{
	*philo_args = (t_philo_args *)malloc(sizeof(t_philo_args) * n_philos);
	if (*philo_args == NULL)
		return (false);
	return (true);
}

bool	init_philo_args(t_main_args *main_args, t_philo_args **philo_args, \
						t_shared_args *shared_args)
{
	size_t	idx;

	if (alloc_philo_args(main_args->n_philos, philo_args) == false)
		return (false);
	idx = 0;
	shared_args->is_end = false;
	while (idx < main_args->n_philos)
	{
		(*philo_args)[idx].id = idx + 1;
		(*philo_args)[idx].time_eat = main_args->time_eat;
		(*philo_args)[idx].time_sleep = main_args->time_sleep;
		(*philo_args)[idx].n_eat = 0;
		(*philo_args)[idx].left_fork = &((*philo_args)[idx]._fork);
		(*philo_args)[idx].right_fork = &((*philo_args)[(idx + 1) % \
										  main_args->n_philos]._fork);
		(*philo_args)[idx].is_end = &(shared_args->is_end);
		(*philo_args)[idx].is_end_lock = &(shared_args->is_end_lock);
		idx++;
	}
	return (true);
}
