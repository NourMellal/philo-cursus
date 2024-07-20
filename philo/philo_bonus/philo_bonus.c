/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:56:35 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 19:08:05 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_pids(t_state *state)
{
	int	return_value;
	int	count;

	count = 0;
	while (count < state->pids_count)
	{
		if (waitpid(-1, &return_value, 0) == -1)
		{
			printf(WAIT_FAILED);
			return (kill_proc_and_free(state));
		}
		if (return_value)
		{
			count++;
			break ;
		}
		count++;
	}
	if (count < state->pids_count)
		kill_proc_and_free(state);
	else
		unlink_sem_and_free(state);
}

void	start_simulation(t_state *state)
{
	state->philos = malloc(sizeof(t_philo) * state->philos_count);
	state->pids = malloc(sizeof(int) * state->philos_count);
	if (!state->philos || !state->pids)
	{
		printf(MALLOC_FAILED);
		return (free_all(state));
	}
	if (init_global_mutexes(state))
		return (unlink_sem_and_free(state));
	setup_philos(state);
	state->pids_count = start_philos(state);
	if (state->pids_count != state->philos_count)
		return (kill_proc_and_free(state));
	wait_pids(state);
}
