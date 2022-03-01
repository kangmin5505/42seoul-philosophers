/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:27:20 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/01 16:26:35 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static enum e_exit_status	print_msg(enum e_exit_status exit_status)
{
	size_t	len;
	static const char	*msg[] = {
		"",
		"Usage: ./philo n_phios time_die time_eat time_sleep [n_must_eat]\n",
		"Error: Allocation fail\n",
		"Error: Mutex fail\n",
		"Error: Runtime fail\n"
	};

	if (exit_status == SUCCESS)
		return (SUCCESS);
	len = ft_strlen(msg[exit_status]);
	write(STDERR_FILENO, msg[exit_status], len);
	return (exit_status);
}

int	main(int argc, const char **argv)
{
	int			result;
	t_main_args	main_args;

	result = SUCCESS;
	if (parse_input(argc, argv, &main_args) == false)
		return (print_msg(PARSE_FAIL));
	return (print_msg(result));
}
