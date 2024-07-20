/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:52:14 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 18:52:18 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes_and_free(t_state *state, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&state->forks[i]);
		i++;
	}
	free(state->philos);
}

void	join_threads(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philos_count)
	{
		pthread_join(state->philos[i].thread, NULL);
		i++;
	}
}

void	destroy_all(t_state *state)
{
	join_threads(state);
	pthread_mutex_destroy(&state->death);
	pthread_mutex_destroy(&state->write);
	destroy_mutexes_and_free(state, state->philos_count);
}
