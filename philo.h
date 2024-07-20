#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define INT_MAX 2147483647
#define MUTEX_INIT_FAILED "Mutex init failed, can't start simulation.\n"
#define MALLOC_FAILED "MALLOC failed, can't start simulation.\n"
#define THREAD_INIT_FAILED "Thread creation failed, can't start simulation.\n"
#define THREAD_JOIN_FAILED "Thread joining failed, can't start simulation.\n"
#define FORK_MSG "has taken a fork"
#define EAT_MSG "is eating"
#define SLEEP_MSG "is sleeping"
#define THINK_MSG "is thinking"
#define DIED_MSG "died"

typedef struct s_simul
{
	int				exit;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_cap;
}					t_simul;

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
	t_simul			*sim;
}					t_philo;

typedef struct s_state
{
	int				is_valid;
	int				philos_count;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
	t_simul			sim;
}					t_state;

t_state	parse_args(int ac, char **av);
int set_int(char *s, int *val);
int get_long(char *s);
int is_valid_num(char *s);

#endif
