/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:03:00 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/04 08:55:45 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/time.h>

void	set_sem_name(char *name, size_t id)
{
	static const char	*base_name = SEM_NAME_PHILO;
	unsigned int		idx;

	idx = 0;
	while (base_name[idx])
	{
		name[idx] = base_name[idx];
		idx++;
	}
	name[idx++] = (id % 10) + '0';
	id /= 10;
	while (id)
	{
		name[idx++] = (id % 10) + '0';
		id /= 10;
	}
	name[idx] = '\0';
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

t_timestamp	get_timestamp_in_ms(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	synchronized_status_log(t_philo_args *philo_args, \
								t_shared_args *shared_args, const char *msg)
{
	sem_wait(shared_args->is_end_lock);
	printf("%zu %zu %s\n", get_timestamp_in_ms() - \
		   philo_args->start_time, philo_args->id, msg);
	sem_post(shared_args->is_end_lock);
}

void	smart_sleep(t_timestamp	target_time)
{
	t_timestamp	sleep_start;

	sleep_start = get_timestamp_in_ms();
	while (get_timestamp_in_ms() - sleep_start <= target_time)
		usleep(EPSILON);
}
