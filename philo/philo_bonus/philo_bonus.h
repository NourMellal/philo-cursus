/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msitni <msitni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:56:45 by msitni            #+#    #+#             */
/*   Updated: 2024/03/06 18:56:46 by msitni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define INT_MAX 2147483647
// semaphores path
# define FORKS_SEM_PATH "/philos_forks.sem"
# define WRITE_SEM_PATH "/philos_write.sem"
// errors..
# define PROC_INIT_FAILED "Process creation failed, can't start simulation.\n"
# define SEM_INIT_FAILED "Semaphore creation failed, can't start simulation.\n"
# define MALLOC_FAILED "MALLOC failed, can't start simulation.\n"
# define MUTEX_INIT_FAILED "Mutex init failed, can't start simulation.\n"
# define WAIT_FAILED "WAIT_PID failed, can't start simulation.\n"
# define THREAD_INIT_FAILED "Thread creation failed, can't start simulation.\n"
// Actions..
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIED_MSG "died"
// incs..
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_wait
{
	int				pid;
	int				return_value;
}					t_wait;

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
	sem_t			*forks;
	int				forks_count;
	pthread_t		thread;
	sem_t			*write;
	pthread_mutex_t	death;
	size_t			last_meal;
	int				eat_count;
	t_sim			*sim;
}					t_philo;

typedef struct s_state
{
	int				is_valid;
	int				philos_count;
	t_philo			*philos;
	int				pids_count;
	int				*pids;
	sem_t			*forks;
	sem_t			*write;
	t_sim			sim;
}					t_state;

// parsing
t_state				parse_args(int c, char **v);

// simulation
void				start_simulation(t_state *state);
int					init_global_mutexes(t_state *state);
void				setup_philos(t_state *state);
int					start_philos(t_state *state);
void				*philo_routine(void *arg);
void				unlink_sem_and_free(t_state *state);
int					monitor_loop(t_philo *philo);

// free
void				kill_proc_and_free(t_state *state);
void				free_all(t_state *state);
void				close_sem(t_state *state);

// utils
size_t				get_time_ms(void);
void				sleep_ms(size_t duration_ms);
void				display_message(sem_t *write, int num, char *message);

#endif
