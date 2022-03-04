/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:24:39 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/04 08:54:42 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stddef.h>
# include <stdbool.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>

# define EPSILON				1000
# define SEM_NAME_FORKS			"/ft_forks"
# define SEM_NAME_FORKS_PAIR	"/ft_forks_pair"
# define SEM_NAME_FULL_PHILOS	"/ft_full_philos"
# define SEM_NAME_IS_END_LOCK	"/ft_is_end_lock"
# define SEM_NAME_PHILO			"/ft_philo"

typedef size_t					t_timestamp;
typedef struct s_main_args		t_main_args;
typedef struct s_shared_args	t_shared_args;
typedef struct s_philo_args		t_philo_args;
typedef struct s_self_dead_args	t_self_dead_args;
typedef struct s_observer_args	t_observer_args;

struct s_main_args
{
	size_t	n_philos;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	n_must_eat;
	bool	optional_arg;
};

struct s_shared_args
{
	sem_t	*forks;
	sem_t	*forks_pair;
	sem_t	*full_philos;
	sem_t	*is_end_lock;
};

struct s_philo_args
{
	size_t		id;
	size_t		n_eat;
	t_timestamp	start_time;
	t_timestamp	last_eat_time;
	sem_t		*event_lock;
};

struct s_self_dead_args
{
	t_main_args		*main_args;
	t_shared_args	*shared_args;
	t_philo_args	*philo_args;
};

struct s_observer_args
{
	size_t	n_philos;
	pid_t	last_philo;
	sem_t	*full_philos;
};

enum e_exit_status
{
	SUCCESS,
	PARSE_FAIL,
	SEMAPHORE_FAIL,
	RUNTIME_FAIL
};

// parser.c
bool		parse_input(int argc, const char **argv, t_main_args *main_args);
// utils.c
void		set_sem_name(char *name, size_t id);
size_t		ft_strlen(const char *str);
t_timestamp	get_timestamp_in_ms(void);
void		synchronized_status_log(t_philo_args *philo_args, \
								t_shared_args *shared_args, const char *msg);
void		smart_sleep(t_timestamp	target_time);
// semaphore.c
bool		init_semaphore(t_shared_args *shared_args, size_t n_philos);
void		destroy_semaphore(t_shared_args *shared_args);
bool		open_semaphore(const char *name, unsigned int value, \
						   sem_t **target);
// start_dining.c
bool		start_dining(t_main_args *main_args, t_philo_args *philo_args, \
						 t_shared_args *shared_args);
// philo_routine.c
int			philo_routine(t_main_args *main_args, t_philo_args *philo_args, \
						  t_shared_args *shared_args);
// philo_routine_helper.c
void		philo_release_forks(t_shared_args *args);
void		philo_takes_forks(t_philo_args *philo_args, \
							  t_shared_args *shared_args);
// observer.c
void		*check_self_dead(void *_args);
void		*observer_routine(void *_args);
#endif
