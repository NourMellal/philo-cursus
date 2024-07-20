/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:57:17 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 19:04:44 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_start_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->death);
	if (!philo->sim->exit)
	{
		display_message(philo->write, philo->num, EAT_MSG);
		philo->last_meal = get_time_ms();
		philo->eat_count++;
		pthread_mutex_unlock(&philo->death);
	}
	else
		pthread_mutex_unlock(&philo->death);
	sleep_ms(philo->sim->t_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

int	philo_eat(t_philo *philo)
{
	display_message(philo->write, philo->num, "Acquiring forks");
	sem_wait(philo->forks);
	if (!philo->sim->exit)
		display_message(philo->write, philo->num, FORK_MSG);
	if (philo->forks_count == 1)
		return (sem_post(philo->forks) || 1);
	sem_wait(philo->forks);
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
		sleep_ms(20);
	while (1)
	{
		if (philo_eat(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
		pthread_mutex_lock(&philo->death);
		if (philo->sim->exit)
		{
			pthread_mutex_unlock(&philo->death);
			break ;
		}
		pthread_mutex_unlock(&philo->death);
	}
	return (NULL);
}
