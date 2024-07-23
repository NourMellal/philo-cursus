/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:39:44 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/23 18:06:47 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_state *state)
{
	int	i;

	if (state->sim.eat_cap == -1)
		return (0);
	i = 0;
	while (i < state->philos_count
		&& state->philos[i].eat_count >= state->sim.eat_cap)
	{
		i++;
	}
	return (i == state->philos_count);
}

int	check_death(t_state *state)
{
	int		i;
	size_t	res;

	i = 0;
	while (i < state->philos_count)
	{
		res = time_in_ms() - state->philos[i].last_meal;
		if (res > (size_t)state->sim.t_die)
		{
			display_msg(&state->philos[i], DIED_MSG, state->sim.start_time, 0);
			state->sim.exit = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	simul_loop(t_state *state)
{
	while (1)
	{
		sleep_ms(5);
		pthread_mutex_lock(&state->death);
		if (check_death(state) || check_eat(state))
		{
			state->sim.exit = 1;
			pthread_mutex_unlock(&state->death);
			return ;
		}
		pthread_mutex_unlock(&state->death);
	}
}
