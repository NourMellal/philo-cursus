/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:34:02 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/21 23:31:12 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_state state;

	if (ac != 5 && ac != 6)
	{
		printf("Bad arguments.\n");
		return (0);
	}
	state = parse_args(ac - 1, av + 1);
	if (!state.is_valid)
	{
		printf("Invalid arguments values.\n");
		return (0);
	}
	simulation(&state);
	return (0);
}