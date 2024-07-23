/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:05:04 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/23 18:34:38 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_msg(t_philo *philo, char *msg, size_t s_time, int lock)
{
	size_t	time;
	size_t	now;

	if (lock)
		pthread_mutex_lock(philo->death);
	now = time_in_ms();
	time = now - s_time;
	if (philo->sim->exit == 0)
		printf("%lu %d %s", time, philo->num, msg);
	if (lock)
		pthread_mutex_unlock(philo->death);
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
		usleep(750);
}
