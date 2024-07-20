/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:51:46 by msitni            #+#    #+#             */
/*   Updated: 2024/07/19 01:19:30 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks_addresses(t_state *state)
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

	set_forks_addresses(state);
	i = 0;
	while (i < state->philos_count)
	{
		state->philos[i].num = i + 1;
		state->philos[i].eat_count = 0;
		if (pthread_mutex_init(state->philos[i].l_fork, NULL))
		{
			printf(MUTEX_INIT_FAILED);
			return (i);
		}
		i++;
	}
	return (i);
}

int	init_global_mutexes(t_state *state)
{
	if (pthread_mutex_init(&state->death, NULL))
	{
		printf(MUTEX_INIT_FAILED);
		return (1);
	}
	if (pthread_mutex_init(&state->write, NULL))
	{
		pthread_mutex_destroy(&state->death);
		printf(MUTEX_INIT_FAILED);
		return (1);
	}
	return (0);
}

int	create_threads(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philos_count)
	{
		state->philos[i].death = &state->death;
		state->philos[i].write = &state->write;
		state->philos[i].sim = &state->sim;
		if (pthread_create(&(state->philos[i].thread), NULL, &philo_routine,
				&(state->philos[i])))
		{
			printf(THREAD_INIT_FAILED);
			return (1);
		}
		state->philos[i].last_meal = get_time_ms();
		i++;
	}
	return (0);
}
