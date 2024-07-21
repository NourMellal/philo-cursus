/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:02:38 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/21 20:50:50 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulation(t_state *state)
{
	state->philos = malloc(sizeof(t_philo) * state->philos_count);
	if (!state->philos)
	{
		printf(MALLOC_FAILED);
		return ;
	}
	state->forks = malloc(sizeof(pthread_mutex_t) * state->philos_count);
	if (!state->forks)
	{
		free(state->philos);
		printf(MALLOC_FAILED);
		return ;
	}
	memset(state->philos, 0, sizeof(t_philo) * state->philos_count);
	memset(state->forks, 0, sizeof(pthread_mutex_t) * state->philos_count);
	state->sim.exit = 0;
	if (setup_philos(state) != state->philos_count || init_gmutexes(state)
		|| thrds_creation(state))
		return (destroy_mutexes_free(state, state->philos_count));
	simul_loop(state);
	to_destroy(state);
}
