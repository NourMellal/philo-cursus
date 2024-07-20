/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:58:33 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 19:55:23 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_for_death(t_philo *philo)
{
	long	result;

	result = get_time_ms() - philo->last_meal;
	if (result > philo->sim->t_die)
	{
		sem_wait(philo->write);
		display_message(NULL, philo->num, DIED_MSG);
		return (1);
	}
	return (0);
}

int	check_for_eat(t_philo *philo)
{
	if (philo->sim->eat_cap == -1)
		return (0);
	return (philo->eat_count >= philo->sim->eat_cap);
}

int	monitor_loop(t_philo *philo)
{
	int	exit_value;

	while (1)
	{
		pthread_mutex_lock(&philo->death);
		if (check_for_death(philo))
		{
			philo->sim->exit = 1;
			exit_value = 1;
			pthread_mutex_unlock(&philo->death);
			break ;
		}
		if (check_for_eat(philo))
		{
			philo->sim->exit = 1;
			exit_value = 0;
			pthread_mutex_unlock(&philo->death);
			break ;
		}
		pthread_mutex_unlock(&philo->death);
		sleep_ms(5);
	}
	return (exit_value);
}
