/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:25:19 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/23 18:05:14 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_lr_forks(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philos_count)
	{
		state->philos[i].l_fork = &state->forks[i];
		state->philos[i].r_fork = &state->forks[(i + 1) % state->philos_count];
		i++;
	}
}

int	setup_philos(t_state *state)
{
	int	i;

	i = 0;
	set_lr_forks(state);
	while (i < state->philos_count)
	{
		state->philos[i].num = i + 1;
		state->philos[i].eat_count = 0;
		state->philos[i].sim = &state->sim;
		state->philos[i].death = &state->death;
		if (pthread_mutex_init(&state->forks[i], NULL))
		{
			printf(MUTEX_INIT_FAILED);
			return (i);
		}
		i++;
	}
	return (i);
}

int	init_gmutexes(t_state *state)
{
	if (pthread_mutex_init(&state->death, NULL))
	{
		printf(MUTEX_INIT_FAILED);
		return (1);
	}
	return (0);
}

int	thrds_creation(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philos_count)
	{
		state->philos[i].last_meal = time_in_ms();
		if (pthread_create(&(state->philos[i].thread), NULL, &routine,
				&(state->philos[i])))
		{
			printf(THREAD_INIT_FAILED);
			return (1);
		}
		i++;
	}
	return (0);
}
