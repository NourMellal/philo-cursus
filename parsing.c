/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:55:22 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/22 17:11:34 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	return (!s[i] && i);
}

int	get_long(char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + (s[i] - '0');
		if (res > INT_MAX)
			return (res);
		i++;
	}
	return (res);
}

int	set_int(char *s, int *val)
{
	long	res;

	if (!is_valid_num(s))
		return (1);
	res = get_long(s);
	if (res > INT_MAX)
		return (1);
	*val = (int)res;
	return (0);
}

t_state	parse_args(int ac, char **av)
{
	t_state	state;

	state.is_valid = 0;
	if (set_int(av[0], &state.philos_count) || !state.philos_count)
		return (state);
	if (set_int(av[1], &state.sim.t_die))
		return (state);
	if (set_int(av[2], &state.sim.t_eat))
		return (state);
	if (set_int(av[3], &state.sim.t_sleep))
		return (state);
	if (ac == 5)
	{
		if (set_int(av[4], &state.sim.eat_cap))
			return (state);
	}
	else
		state.sim.eat_cap = -1;
	state.is_valid = 1;
	state.sim.start_time = time_in_ms();
	return (state);
}
