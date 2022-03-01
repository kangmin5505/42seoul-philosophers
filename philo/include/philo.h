/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:24:39 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/01 16:26:49 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_main_args	t_main_args;

struct s_main_args
{
	size_t	n_philos;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	n_must_eat;
	bool	optional_arg;
};

enum e_exit_status
{
	SUCCESS,
	PARSE_FAIL,
	ALLOC_FAIL,
	MUTEX_FAIL,
	RUNTIME_FAIL
};

size_t			ft_strlen(const char *str);
bool			parse_input(int argc, const char **argv, t_main_args *main_args);
#endif
