/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:56:04 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/21 16:15:27 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes_free(t_state *state, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		pthread_mutex_destroy(&state->forks[i]);
		i++;
	}
	free(state->philos);
	free(state->forks);
}

void	join_thrds(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philos_count)
	{
		pthread_join(state->philos[i].thread, NULL);
		i++;
	}
}

void	to_destroy(t_state *state)
{
	join_thrds(state);
	pthread_mutex_destroy(&state->death);
	pthread_mutex_destroy(&state->write);
	destroy_mutexes_free(state, state->philos_count);
}
