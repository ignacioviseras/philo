/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:56:01 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/04 19:13:30 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_ptcode
{
	INIT,
	CREATE,
	JOIN,
	DETACH,
	LOCK,
	UNLOCK,
	DESTROY,
}						t_ptcode;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef enum e_time
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}						t_time;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_data	t_data;
typedef struct s_philo
{
	int					id;
	long				eat_cnt;
	bool				full;
	long				last_eat;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_mutex_t		phil_mtx;
	pthread_t			thread_id;
	t_data				*data;

}						t_philo;

typedef struct s_data
{
	int					n_philo;
	int					tm_die;
	int					tm_eat;
	int					tm_sleep;
	int					max_eats;
	long				init_time;
	bool				end_time;
	bool				threads_ready;
	long				n_threads_running;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		mutx;
	pthread_mutex_t		print_mutx;

}						t_data;

void					write_status(t_philo_status status, t_philo *philo);
int						error_msg(const char *error);
long					ft_atol(const char *nptr);
int						control_errs(char *str_num);
void					set_bool(pthread_mutex_t *mutex, bool *dest,
							bool value);
bool					get_bool(pthread_mutex_t *mutex, bool *value);
long					get_long(pthread_mutex_t *mutex, long *value);
void					set_long(pthread_mutex_t *mutex, long *dest,
							long value);
bool					simulation_finish(t_data *data);
void					set_bool(pthread_mutex_t *mutex, bool *dest,
							bool value);
bool					get_bool(pthread_mutex_t *mutex, bool *value);
long					get_long(pthread_mutex_t *mutex, long *value);
void					set_long(pthread_mutex_t *mutex, long *dest,
							long value);
bool					simulation_finish(t_data *data);
void					thinking(t_philo *philo, bool simulation);
void					eat(t_philo *philo);
void					wait_all(t_data *data);
bool					thread_running(pthread_mutex_t *mutex, long *threads,
							long n_philo);
void					increase_long(pthread_mutex_t *mutex, long *value);
void					desyncronize(t_philo *philo);
void					*dinner_simulat(void *data);
bool					philo_die(t_philo *philo);
void					*monitor_dinner(void *tdata);
void					*one_philo(void *data);
void					clean(t_data *data);
void					init_dinner(t_data *data);
int						have_max_eats(t_data *data, char *argv);
int						init_params(t_data *data, char **argv);
void					get_fork(t_philo *philo, t_fork *fork, int pos);
void					init_philo(t_data *data);
int						init_data(t_data *data);
int						mtx_errors(int status, t_ptcode pt_code);
int						handle_mtx(pthread_mutex_t *mtx, t_ptcode ptcode);
int						thread_errors(int status, t_ptcode pt_code);
int						handle_thread(pthread_t *thread, void *(*f)(void *),
							void *data, t_ptcode ptcode);
long					get_tm(t_time time_e);
void					percise_usleep(long usec, t_data *data);

#endif