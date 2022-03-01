/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:24:39 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/01 19:54:15 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

//==================== Typedef  ====================

typedef size_t					t_timestamp;
typedef struct	s_main_args		t_main_args;
typedef struct	s_philo_args	t_philo_args;
typedef struct	s_shared_args	t_shared_args;

struct s_main_args
{
	size_t	n_philos;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	n_must_eat;
	bool	optional_arg;
};

struct s_philo_args
{
	pthread_t		philo;
	size_t			id;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			n_eat;
	t_timestamp		start_time;
	t_timestamp		last_eat_time;
	pthread_mutex_t	_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	event_lock;
	bool			*is_end;
	pthread_mutex_t	*is_end_lock;
};

struct	s_shared_args
{
	bool			is_end;
	pthread_mutex_t	is_end_lock;
};

enum e_exit_status
{
	SUCCESS,
	PARSE_FAIL,
	ALLOC_FAIL,
	MUTEX_FAIL,
	RUNTIME_FAIL
};

//==================== Prototype ====================

size_t	ft_strlen(const char *str);
bool	parse_input(int argc, const char **argv, t_main_args *main_args);
bool	init_philo_args(t_main_args *main_args, t_philo_args **philo_args, t_shared_args *shared_args);
bool	init_mutex(size_t n_philos, t_philo_args *philo_args, t_shared_args *shared_args);
void	destroy_mutex(size_t n_philos, t_philo_args *philo_args, t_shared_args *shared_args);
#endif
