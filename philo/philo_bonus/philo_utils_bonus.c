/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:57:30 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 19:10:14 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_philo(t_state *state, int num)
{
	int		exit_value;
	t_philo	philo;

	philo = state->philos[num];
	free_all(state);
	if (pthread_mutex_init(&philo.death, NULL))
	{
		printf(MUTEX_INIT_FAILED);
		close_sem(state);
		exit(1);
	}
	philo.last_meal = get_time_ms();
	if (pthread_create(&(philo.thread), NULL, &philo_routine, &(philo)))
	{
		printf(THREAD_INIT_FAILED);
		pthread_mutex_destroy(&philo.death);
		close_sem(state);
		pthread_mutex_destroy(&philo.death);
		exit(1);
	}
	exit_value = monitor_loop(&philo);
	pthread_join(philo.thread, NULL);
	close_sem(state);
	pthread_mutex_destroy(&philo.death);
	exit(exit_value);
}

int	start_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philos_count)
	{
		state->pids[i] = fork();
		if (!state->pids[i])
			start_philo(state, i);
		if (state->pids[i] == -1)
		{
			printf(PROC_INIT_FAILED);
			return (i);
		}
		i++;
	}
	return (i);
}

int	init_global_mutexes(t_state *state)
{
	state->sim.exit = 0;
	sem_unlink(FORKS_SEM_PATH);
	sem_unlink(WRITE_SEM_PATH);
	state->forks = sem_open(FORKS_SEM_PATH, O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, state->philos_count);
	state->write = sem_open(WRITE_SEM_PATH, O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
	if (!state->forks || !state->write)
	{
		printf(SEM_INIT_FAILED);
		return (1);
	}
	return (0);
}

void	setup_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philos_count)
	{
		state->philos[i].num = i + 1;
		state->philos[i].eat_count = 0;
		state->philos[i].forks = state->forks;
		state->philos[i].forks_count = state->philos_count;
		state->philos[i].write = state->write;
		state->philos[i].sim = &state->sim;
		i++;
	}
}
