/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:52:02 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 18:52:18 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define INT_MAX 2147483647
// errors..
# define MUTEX_INIT_FAILED "Mutex init failed, can't start simulation.\n"
# define MALLOC_FAILED "MALLOC failed, can't start simulation.\n"
# define THREAD_INIT_FAILED "Thread creation failed, can't start simulation.\n"
# define THREAD_JOIN_FAILED "Thread joining failed, can't start simulation.\n"
// Actions..
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIED_MSG "died"
// incs..
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_sim
{
	int				exit;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_cap;
}					t_sim;

typedef struct s_philo
{
	int				num;
	pthread_t		thread;
	pthread_mutex_t	*write;
	pthread_mutex_t	*death;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	size_t			last_meal;
	int				eat_count;
	//    int is_eating;
	t_sim			*sim;
}					t_philo;

typedef struct s_state
{
	int				is_valid;
	int				philos_count;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
	t_sim			sim;
}					t_state;

t_state				parse_args(int c, char **v);
int					init_global_mutexes(t_state *state);
void				start_simulation(t_state *state);
void				destroy_mutexes_and_free(t_state *state, int count);
int					setup_philos(t_state *state);
int					create_threads(t_state *state);
void				*philo_routine(void *arg);
size_t				get_time_ms(void);
void				sleep_ms(size_t duration_ms);
void				destroy_all(t_state *state);
void				display_message(pthread_mutex_t *write, int num,
						char *message);

#endif
