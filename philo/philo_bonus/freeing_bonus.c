/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:59:20 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 18:59:47 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_state *state)
{
	if (state->pids)
		free(state->pids);
	if (state->philos)
		free(state->philos);
}

void	close_sem(t_state *state)
{
	sem_close(state->forks);
	sem_close(state->write);
}

void	unlink_sem_and_free(t_state *state)
{
	close_sem(state);
	sem_unlink(FORKS_SEM_PATH);
	sem_unlink(WRITE_SEM_PATH);
	free_all(state);
}

void	kill_proc_and_free(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->pids_count)
	{
		kill(state->pids[i], SIGKILL);
		i++;
	}
	unlink_sem_and_free(state);
}
