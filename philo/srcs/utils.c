/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:11:01 by kangkim           #+#    #+#             */
/*   Updated: 2022/03/01 23:27:08 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

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

void	sychronized_status_log(t_philo_args *arg, const char *str)
{
	pthread_mutex_lock(&(arg->event_lock));
	if (*(arg->is_end) == false)
		printf("%zu %zu %s\n", get_timestamp_in_ms() - arg->start_time, arg->id, str);
	pthread_mutex_unlock(&(arg->event_lock));
}

void	smart_sleep(t_timestamp	target_time)
{
	t_timestamp	sleep_start;

	sleep_start = get_timestamp_in_ms();
	while (get_timestamp_in_ms() - sleep_start <= target_time)
		usleep(EPSILON);
}
