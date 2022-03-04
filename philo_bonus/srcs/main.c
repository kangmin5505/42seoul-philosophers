/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:27:43 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/04 09:17:05 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static enum e_exit_status	print_msg(enum e_exit_status exit_status)
{
	size_t				len;
	static const char	*msg[] = {
		"",
		"Usage: ./philo n_philos time_die time_eat time_sleep [n_must_eat]\n",
		"Error: Semaphore fail\n",
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
	enum e_exit_status	result;
	t_main_args			main_args;
	t_philo_args		philo_args;
	t_shared_args		shared_args;

	result = SUCCESS;
	if (parse_input(argc, argv, &main_args) == false)
		return (print_msg(PARSE_FAIL));
	if (init_semaphore(&shared_args, main_args.n_philos) == false)
		return (print_msg(SEMAPHORE_FAIL));
	if (start_dining(&main_args, &philo_args, &shared_args) == false)
		result = RUNTIME_FAIL;
	destroy_semaphore(&shared_args);
	return (print_msg(result));
}
