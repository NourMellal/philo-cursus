/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:52:13 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 18:52:18 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(pthread_mutex_t *write, int num, char *message)
{
	size_t	timestamp;

	pthread_mutex_lock(write);
	timestamp = get_time_ms();
	printf("%lu %d %s\n", timestamp, num, message);
	pthread_mutex_unlock(write);
}

size_t	get_time_ms(void)
{
	struct timeval	now;
	size_t			result;

	gettimeofday(&now, NULL);
	result = now.tv_sec * 1000;
	result += now.tv_usec / 1000;
	return (result);
}

void	sleep_ms(size_t duration_ms)
{
	size_t	then;
	size_t	now;

	then = get_time_ms();
	while (1)
	{
		now = get_time_ms();
		if (now - then > duration_ms)
			return ;
		usleep(500);
	}
}
