/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:59:03 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 19:03:07 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
