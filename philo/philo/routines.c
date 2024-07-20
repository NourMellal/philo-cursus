/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:51:56 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 18:52:18 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (!philo->sim->exit)
	{
		display_message(philo->write, philo->num, EAT_MSG);
		philo->last_meal = get_time_ms();
		philo->eat_count++;
		pthread_mutex_unlock(philo->death);
	}
	else
		pthread_mutex_unlock(philo->death);
	sleep_ms(philo->sim->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (!philo->sim->exit)
		display_message(philo->write, philo->num, FORK_MSG);
	if (philo->r_fork == philo->l_fork)
		return (pthread_mutex_unlock(philo->r_fork) || 1);
	pthread_mutex_lock(philo->l_fork);
	if (!philo->sim->exit)
		display_message(philo->write, philo->num, FORK_MSG);
	philo_start_eat(philo);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	if (!philo->sim->exit)
		display_message(philo->write, philo->num, SLEEP_MSG);
	sleep_ms(philo->sim->t_sleep);
}

void	philo_think(t_philo *philo)
{
	if (!philo->sim->exit)
		display_message(philo->write, philo->num, THINK_MSG);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->num % 2 == 0)
		sleep_ms(3);
	while (1)
	{
		if (philo_eat(philo))
			return (NULL);
		philo_sleep(philo);
		philo_think(philo);
		pthread_mutex_lock(philo->death);
		if (philo->sim->exit)
		{
			pthread_mutex_unlock(philo->death);
			break ;
		}
		pthread_mutex_unlock(philo->death);
	}
	return (NULL);
}
