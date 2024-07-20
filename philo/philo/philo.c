/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:51:54 by msitni            #+#    #+#             */
/*   Updated: 2024/07/20 22:00:04 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_death(t_state *state)
{
	long	result;
	int		i;

	i = 0;
	while (i < state->philos_count)
	{
		result = get_time_ms() - state->philos[i].last_meal;
		if (result > state->sim.t_die)
		{
			display_message(&state->write, i + 1, DIED_MSG);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_for_eat(t_state *state)
{
	int	i;

	if (state->sim.eat_cap == -1)
		return (0);
	i = 0;
	while (i < state->philos_count
		&& state->philos[i].eat_count >= state->sim.eat_cap)
		i++;
	return (i == state->philos_count);
}

void	simulation_loop(t_state *state)
{
	(void)state;
	while (1)
	{
		sleep_ms(5);
		pthread_mutex_lock(&state->death);
		if (check_for_death(state) || check_for_eat(state))
		{
			state->sim.exit = 1;
			pthread_mutex_unlock(&state->death);
			return ;
		}
		pthread_mutex_unlock(&state->death);
	}
}

void	start_simulation(t_state *state)
{
	int	mutex_count;

	state->philos = malloc((sizeof(t_philo) + sizeof(pthread_mutex_t))
			* state->philos_count);
	if (!state->philos)
	{
		printf(MALLOC_FAILED);
		return ;
	}
	memset(state->philos, 0, (sizeof(t_philo) + sizeof(pthread_mutex_t))
		* state->philos_count);
	state->forks = (pthread_mutex_t *)(state->philos + state->philos_count);
	state->sim.exit = 0;
	mutex_count = setup_philos(state);
	if (mutex_count != state->philos_count || init_global_mutexes(state))
		return (destroy_mutexes_and_free(state, mutex_count));
	if (create_threads(state))
		return (destroy_mutexes_and_free(state, state->philos_count));
	simulation_loop(state);
	destroy_all(state);
}
