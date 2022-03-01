/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:56:09 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/01 16:25:52 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_digit(const char c)
{
	return ('0' <= c && c <= '9');
}

static size_t	arr_to_num(const char *str)
{
	size_t	num;
	size_t	len;

	num = 0;
	len = 0;
	while (is_digit(str[len]))
	{
		num = num * 10 + (str[len] - '0');
		len++;
	}
	if (len == 0 || str[len] != '\0')
		return (0);
	return (num);
}

static bool	parse_required(const char **argv, t_main_args *main_args)
{
	main_args->n_philos = arr_to_num(argv[1]);
	if (main_args->n_philos == 0)
		return (false);
	main_args->time_die = arr_to_num(argv[2]);
	if (main_args->time_die == 0)
		return (false);
	main_args->time_eat = arr_to_num(argv[3]);
	if (main_args->time_eat == 0)
		return (false);
	main_args->time_sleep = arr_to_num(argv[4]);
	if (main_args->time_sleep == 0)
		return (false);
	main_args->optional_arg = false;
	return (true);
}

static bool	parse_optional(const char **argv, t_main_args *main_args)
{
	if (parse_required(argv, main_args) == false)
		return (false);
	main_args->n_must_eat = arr_to_num(argv[5]);
	if (main_args->n_must_eat == 0)
		return (false);
	return (true);
}

bool	parse_input(int argc, const char **argv, t_main_args *main_args)
{
	if (argc == 5 && parse_required(argv, main_args) == true)
		return (true);
	if (argc == 6 && parse_optional(argv, main_args) == true)
		return (true);
	return (false);
}
