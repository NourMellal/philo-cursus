/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmellal <nmellal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:34:02 by nmellal           #+#    #+#             */
/*   Updated: 2024/07/20 21:58:54 by nmellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    simulation(t_state *state)
{
    state->philos = malloc(sizeof(t_philo) * state->philos_count);
    if (!state->philos)
    {
        printf(MALLOC_FAILED);
        return ;
    }
    state->forks = malloc(sizeof(pthread_mutex_t) * state->philos_count);
    if (!state->forks)
    {
        free(state->philos);
        printf(MALLOC_FAILED);
        return;
    }
    memset(state->philos, 0, sizeof(t_philo) * state->philos_count);
    memset(state->forks, 0, sizeof(pthread_mutex_t) * state->philos_count);
    state->sim.exit = 0;
    
}

int main(int ac, char *av)
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
}