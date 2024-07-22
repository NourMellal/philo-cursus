/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:05:04 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/22 18:30:22 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_msg(pthread_mutex_t *write, int num, char *msg, size_t s_time)
{
	size_t	time;
	size_t	now;

	pthread_mutex_lock(write);
	now = time_in_ms();
	time = now - s_time;
	printf("%lu %d %s", time, num, msg);
	pthread_mutex_unlock(write);
}

size_t	time_in_ms(void)
{
	struct timeval	time;
	size_t			res;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000;
	res += time.tv_usec / 1000;
	return (res);
}

void	sleep_ms(size_t ms)
{
	size_t	then;

	then = time_in_ms();
	while (time_in_ms() - then < ms)
		usleep(200);
}
