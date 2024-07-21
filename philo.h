#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define MUTEX_INIT_FAILED "Mutex init failed, can't start simulation.\n"
# define MALLOC_FAILED "MALLOC failed, can't start simulation.\n"
# define THREAD_INIT_FAILED "Thread creation failed, can't start simulation.\n"
# define THREAD_JOIN_FAILED "Thread joining failed, can't start simulation.\n"
# define FORK_MSG "has taken a fork\n"
# define EAT_MSG "is eating\n"
# define SLEEP_MSG "is sleeping\n"
# define THINK_MSG "is thinking\n"
# define DIED_MSG "died\n"

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

t_state				parse_args(int ac, char **av);
int					set_int(char *s, int *val);
int					get_long(char *s);
int					is_valid_num(char *s);

void				simulation(t_state *state);
int					setup_philos(t_state *state);
void				set_lr_forks(t_state *state);
int					thrds_creation(t_state *state);
int					init_gmutexes(t_state *state);

size_t				time_in_ms(void);
void				display_msg(pthread_mutex_t *write, int num, char *msg);
void				sleep_ms(size_t ms);

int					check_death(t_state *state);
int					check_eat(t_state *state);
void				simul_loop(t_state *state);

void				destroy_mutexes_free(t_state *state, int end);
void				join_thrds(t_state *state);
void				to_destroy(t_state *state);

void				*routine(void *arg);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
void				is_eating(t_philo *philo);

#endif
