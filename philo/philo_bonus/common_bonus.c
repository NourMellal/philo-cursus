/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:56:18 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 19:54:56 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	display_message(sem_t *write, int num, char *message)
{
	size_t	timestamp;

	if (write)
		sem_wait(write);
	timestamp = get_time_ms();
	printf("%lu %d %s\n", timestamp, num, message);
	if (write)
		sem_post(write);
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
