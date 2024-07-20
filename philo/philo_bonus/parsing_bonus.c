/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:55:48 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 18:55:49 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_valid_num(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	return (!s[i] && i);
}

long	get_long(char *s)
{
	int		i;
	long	value;

	i = 0;
	if (s[i] == '+')
		i++;
	value = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		value = (value * 10) + (s[i] - '0');
		if (value > INT_MAX)
			return (value);
		i++;
	}
	return (value);
}

int	set_int(char *s, int *value)
{
	long	result;

	if (!is_valid_num(s))
		return (1);
	result = get_long(s);
	if (result > INT_MAX)
		return (1);
	*value = (int)result;
	return (0);
}

t_state	parse_args(int c, char **v)
{
	t_state	state;

	state.is_valid = 0;
	if (set_int(v[0], &state.philos_count) || !state.philos_count)
		return (state);
	if (set_int(v[1], &state.sim.t_die))
		return (state);
	if (set_int(v[2], &state.sim.t_eat))
		return (state);
	if (set_int(v[3], &state.sim.t_sleep))
		return (state);
	if (c == 5)
	{
		if (set_int(v[4], &state.sim.eat_cap))
			return (state);
	}
	else
		state.sim.eat_cap = -1;
	state.is_valid = 1;
	return (state);
}
