/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:56:07 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/22 17:15:17 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (!philo->sim->exit)
	{
		display_msg(philo->write, philo->num, EAT_MSG, philo->sim->start_time);
		philo->last_meal = time_in_ms();
		philo->eat_count++;
		pthread_mutex_unlock(philo->death);
	}
	else
		pthread_mutex_unlock(philo->death);
	sleep_ms(philo->sim->t_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (!philo->sim->exit)
		display_msg(philo->write, philo->num, FORK_MSG, philo->sim->start_time);
	if (philo->r_fork == philo->l_fork)
		return (pthread_mutex_unlock(philo->l_fork) || 1);
	pthread_mutex_lock(philo->r_fork);
	if (!philo->sim->exit)
		display_msg(philo->write, philo->num, FORK_MSG, philo->sim->start_time);
	is_eating(philo);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	if (!philo->sim->exit)
		display_msg(philo->write, philo->num, SLEEP_MSG,
			philo->sim->start_time);
	sleep_ms(philo->sim->t_sleep);
}

void	philo_think(t_philo *philo)
{
	if (!philo->sim->exit)
		display_msg(philo->write, philo->num, THINK_MSG,
			philo->sim->start_time);
}

void	*routine(void *arg)
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
