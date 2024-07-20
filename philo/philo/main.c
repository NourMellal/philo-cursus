/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:52:05 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 18:52:18 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int c, char **v)
{
	t_state	state;

	if (c != 5 && c != 6)
	{
		printf("Bad arguments.\n");
		return (0);
	}
	state = parse_args(c - 1, v + 1);
	if (!state.is_valid)
	{
		printf("Invalid arguments values.\n");
		return (0);
	}
	start_simulation(&state);
}
