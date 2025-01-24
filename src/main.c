/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/24 17:39:43 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
◦ number_of_philosophers: es el número de filósofos, pero
	también el número de tenedores.

◦ time_to_die (en milisegundos): si un filósofo no empieza a comer en 
	time_to_die milisegundos desde el comienzo de su ultima comida 
	o desde el principio de la simulación, este morirá.

◦ time_to_eat (en milisegundos): es el tiempo que tiene un filósofo 
	para comer.
	Durante ese tiempo, tendrá los tenedores ocupados.

◦ time_to_sleep (en milisegundos): es el tiempo que tiene un filósofo 
	para dormir.

*******************    ARGUMENTO OPCIONAL    *******************
◦ number_of_times_each_philosopher_must_eat (ARGUMENTO OPCIONAL): si 
	todos los filósofos comen al menos 
	number_of_times_each_philosopher_must_eat veces,
	la simulación se detendrá. Si no se especifica, la simulación 
	se detendrá con la muerte de un filósofo
*/

void write_status(t_philo_status status, t_philo *philo)
{
	long elapsed;

	elapsed = get_tm(MILISECOND);
	handle_mtx(&philo->data->print_mutx, LOCK);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !simulation_finish(philo->data))
		printf("%-6ld %d has taken fork\n", elapsed, philo->id);
	else if (EATING == status && !simulation_finish(philo->data))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finish(philo->data))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finish(philo->data))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-6ld %d died \n", elapsed, philo->id);
	handle_mtx(&philo->data->print_mutx, UNLOCK);
	
}

int error_msg(const char *error)
{
	printf("%s\n", error);
	return (0);
}


long	ft_atol(const char *nptr)
{
	int		index;
	long	sing;
	long	num;

	if (!nptr || *nptr == '\0')
    	return (0);
	sing = 1;
	index = 0;
	num = 0;
	while ((nptr[index] >= 9 && nptr[index] <= 13) || (nptr[index] == 32))
		index++;
	if (nptr[index] == '-')
	{
		sing = -1;
		index++;
	}
	else if (nptr[index] == '+')
		index++;
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		num = num * 10 + (nptr[index++] - '0');
		if ((num * sing) < INT_MIN || (num * sing) > INT_MAX)
			return ((long)INT_MAX + 1);
	}
	return (num * sing);
}


int	control_errs(char *str_num)
{
	long num;
	
	num = ft_atol(str_num);
	if (num <= 0)
	{
		error_msg("Invalid negative number");
		return (0);
	}
	if (num < INT_MIN || num > INT_MAX)
	{
		error_msg("Only unsigned int numbers can be used");
		return (0);
	}
	return (1);// num ok
}

void set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	handle_mtx(mutex, LOCK);
	*dest = value;
	handle_mtx(mutex, UNLOCK);
}

bool get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool ret;
	
	handle_mtx(mutex, LOCK);
	ret = *value;
	handle_mtx(mutex, UNLOCK);
	return (ret);
}

long get_long(pthread_mutex_t *mutex, long *value)
{
	long ret;

	handle_mtx(mutex, LOCK);
	ret = *value;
	handle_mtx(mutex, UNLOCK);
	return (ret);
}

void set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	handle_mtx(mutex, LOCK);
	*dest = value;
	handle_mtx(mutex, UNLOCK);
}

bool simulation_finish(t_data *data)
{
	return (get_bool(&data->mutx, &data->end_time));
}

void thinking(t_philo *philo, bool simulation)
{
	long tm_eat;
	long tm_sleep;
	long tm_think;

	if (!simulation)
		write_status(THINKING, philo);
	if (philo->data->n_philo % 2 == 0)
		return ;
	tm_eat = philo->data->tm_eat;
	tm_sleep = philo->data->tm_sleep;
	tm_think = tm_eat *2 - tm_sleep;
	if (tm_think < 0)
		tm_think = 0;
	percise_usleep(tm_think * 0.42, philo->data);
}

static void eat(t_philo *philo)
{
	handle_mtx(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	handle_mtx(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->phil_mtx, &philo->last_eat, get_tm(MILISECOND));
	philo->eat_cnt++;
	percise_usleep(philo->data->tm_eat, philo->data);
	if (philo->data->max_eats > 0 && philo->eat_cnt == philo->data->max_eats)
		set_bool(&philo->phil_mtx, &philo->full, true);
	handle_mtx(&philo->first_fork->fork, UNLOCK);
	handle_mtx(&philo->second_fork->fork, UNLOCK);

}

/*
	its a while to wait all the threads 
*/
void wait_all(t_data *data)
{
	while (!get_bool(&data->mutx, &data->threads_ready));
}

bool thread_running(pthread_mutex_t *mutex, long *threads, long n_philo)
{
	bool ret;
	ret = false;
	handle_mtx(mutex, LOCK);
	if (*threads == n_philo)
		ret = true;
	handle_mtx(mutex, UNLOCK);
	return (ret);
}

void increase_long(pthread_mutex_t *mutex, long *value)
{
	handle_mtx(mutex, LOCK);
	(*value)++;
	handle_mtx(mutex, UNLOCK);
}

void desyncronize(t_philo *philo)
{
	if (philo->data->n_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			percise_usleep(30000, philo->data);		
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}

void *dinner_simulat(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all(philo->data);
	set_long(&philo->phil_mtx, &philo->last_eat, get_tm(MILISECOND));
	increase_long(&philo->data->mutx, &philo->data->n_threads_running);
	desyncronize(philo);
	while (!simulation_finish(philo->data))
	{
		//comprueba si esta lleno
		if (philo->full)
			break;
		//come
		eat(philo);

		//duerme
		write_status(SLEEPING, philo);//añado modo debug??
		percise_usleep(philo->data->tm_sleep, philo->data);
		//piensa
		thinking(philo, false);
	}
	
	return (NULL);
}

static bool philo_die(t_philo *philo)
{
	long elapsed;
	long tm_to_die;

	if (get_bool(&philo->phil_mtx, &philo->full))
		return (false);
	elapsed = get_tm(MILISECOND)-get_long(&philo->phil_mtx, &philo->last_eat);
	tm_to_die = philo->data->tm_die / 1000;
	if (elapsed > tm_to_die)
		return (true);
	return (false);
}

void *monitor_dinner(void *tdata)
{
	t_data *data;
	int i;

	data = (t_data *)tdata;
	while (!thread_running(&data->mutx, &data->n_threads_running, data->n_philo));
	while (!simulation_finish(data))
	{
		i = -1;
		while (++i < data->n_philo && !simulation_finish(data))
		{
			if (philo_die(data->philos + 1))
			{
				set_bool(&data->mutx, &data->end_time, true);
				write_status(DIED, data->philos + i);
			}
		}
	}
	return (NULL);
}

void *one_philo(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all(philo->data);
	set_long(&philo->phil_mtx, &philo->last_eat, get_tm(MILISECOND));
	increase_long(&philo->data->mutx, &philo->data->n_threads_running);
	write_status(TAKE_FIRST_FORK, philo);
	while(!simulation_finish(philo->data))
		usleep(200);
	return (NULL);
}

void clean(t_data *data)
{
	t_philo *philo;
	int i;

	i = -1;
	while(++i < data->n_philo)
	{
		philo = data->philos + i;
		handle_mtx(&philo->phil_mtx, DESTROY);
	}
	handle_mtx(&data->print_mutx, DESTROY);
	handle_mtx(&data->print_mutx, DESTROY);
	free(data->forks);
	free(data->philos);
}

void init_dinner(t_data *data)
{
	int i;

	i = -1;
	if (0 == data->max_eats)
		return;
	else if (1 == data->n_philo)// ????
		handle_thread(&data->philos[0].thread_id, one_philo, &data->philos[0], CREATE);
	else
	{
		while (++i < data->n_philo)
			handle_thread(&data->philos[i].thread_id, dinner_simulat, &data->philos[i], CREATE);
	}
	handle_thread(&data->monitor, monitor_dinner, data, CREATE);
	data->init_time = get_tm(MILISECOND);
	set_bool(&data->mutx, &data->threads_ready, true);
	i = -1;
	while (++i < data->n_philo)
		handle_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);//SI PASAMOS DE ESTA LINEA TENEMOS TODOS LOS FILOSOFOS
	set_bool(&data->mutx, &data->end_time, true);
	handle_thread(&data->monitor, NULL, NULL, JOIN);
}

int have_max_eats(t_data *data, char *argv)
{
	if (control_errs(argv) == 0)
	{
		data->max_eats = ft_atol(argv);
		return (1);
	}
	error_msg("Error in param 6");
	return (0);
}

int init_params(t_data *data, char **argv)
{
	int x;
	x = 0;
	while (x < 4)
	{	
		if (control_errs(argv[x]) == 0)
			return (0);
		x++;
	}
	data->n_philo = ft_atol(argv[0]);
	data->tm_die = ft_atol(argv[1]) * 1000;
	data->tm_eat = ft_atol(argv[2]) * 1000;
	data->tm_sleep = ft_atol(argv[3]) * 1000;
	if (data->tm_die < 60000 || data->tm_eat < 60000 ||
		data->tm_sleep < 60000)
	{
		error_msg("time major than 6000");
		return (0);
	}
	if (argv[4])
	{
		if (have_max_eats(data, argv[4]) == 0)
			return (0);
	}
	else 
		data->max_eats = -1;
	return (1);
}

static void get_fork(t_philo *philo, t_fork *fork, int pos)
{
	int n_philos;
	
	n_philos = philo->data->n_philo;//fix deadlocks??
	philo->first_fork = &fork[(pos +1) % n_philos];
	philo->second_fork = &fork[pos];
	if (n_philos % 2)
	{
		philo->first_fork = &fork[pos];
		philo->second_fork = &fork[(pos +1) % n_philos];
	}
	
}

static void init_philo(t_data *data)
{
	int i;
	t_philo *philo;

	i = -1;
	while (++i < data->n_philo)
	{
		philo = data->philos +i;
		philo->id = i+1;
		philo->full = false;
		philo->eat_cnt = 0;
		philo->data = data;
		handle_mtx(&philo->phil_mtx, INIT);
		get_fork(philo, data->forks, i);
	}
	
}

int init_data(t_data *data)
{
	int i;

	i = -1;
	data->end_time = false;
	data->threads_ready = false;
	data->n_threads_running = 0;
	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	handle_mtx(&data->mutx, INIT);
	handle_mtx(&data->print_mutx, INIT);
	data->forks = malloc(sizeof(t_fork) * data->n_philo);
	if (!data->philos || !data->forks)
	{
		error_msg("malloc error");
		return (0);
	}
	while (++i < data->n_philo)
	{
		handle_mtx(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	init_philo(data);
	return (1);
}
/*
EINVAL  : 22
EDEADLK : 35
ENOMEM  : 12
EPERM   : 1
EBUSY   : 16
*/
/*
	if the int returned is 0 its al ok
*/
static int mtx_errors(int status, t_ptcode pt_code)
{
	if (status == 0)
		return (0);
	if (status == 22 && (LOCK == pt_code || UNLOCK == pt_code))
		error_msg("The value specified by mutex is invalid");
	else if (status == 22 && INIT == pt_code)
		error_msg("The value specified by attr is invalid");
	else if (status == 35)
		error_msg("A deadlock would occur if the thread blocked waiting for mutex");
	else if (status == 1)
		error_msg("The current thread does not hold a lock on mutex");
	else if (status == 12)
		error_msg("The process cannot allocate enough memory to create another mutex");
	else if (status == 16)
		error_msg("Mutex is locked");
	return (1);
}

/*
	if the int returned is 0 its al ok
*/
int handle_mtx(pthread_mutex_t *mtx, t_ptcode ptcode)
{
	int status;

	status = 0;
	if (LOCK == ptcode)
		status = pthread_mutex_lock(mtx);
	else if (UNLOCK == ptcode)
		status = pthread_mutex_unlock(mtx);
	else if (INIT == ptcode)
		status = pthread_mutex_init(mtx, NULL);
	else if (DESTROY == ptcode)
		status = pthread_mutex_destroy(mtx);
	return (mtx_errors(status, ptcode));
}

/*
EINVAL  : 22
EDEADLK : 35
ENOMEM  : 12
EPERM   : 1
EBUSY   : 16
EAGAIN  : 11
EINVAL  : 22
EPERM   : 1
ESRCH   : 3
EDEADLK : 35
*/

/*
	if the int returned is 0 its al ok
*/
static int thread_errors(int status, t_ptcode pt_code)
{
	if (status == 0)
		return (0);
	if (status == 11)
		error_msg("No resource to create another thread");
	if (status == 1)
		error_msg("No resource to create another thread");
	if (status == 22 && (JOIN == pt_code || DETACH == pt_code))
		error_msg("The value specified by thread is not joinable");
	else if (status == 22 && CREATE == pt_code)
		error_msg("The value specified by attr is invalid");
	else if (status == 35)
		error_msg("A deadlock was detected or the value of *thread specifies the calling thread");
	else if (status == 3)
		error_msg("No thread could be found with this id");
	return (1);
}
/*
	if the int returned is 0 its al ok
*/
int handle_thread(pthread_t *thread, void *(*f)(void *), void *data, t_ptcode ptcode)
{
	int status;

	status = 0;
	if (CREATE == ptcode)
		status = pthread_create(thread, NULL, f, data);
	else if (JOIN == ptcode)
		status = pthread_join(*thread, NULL);
	else if (DETACH == ptcode)
		status = pthread_detach(*thread);
	return (thread_errors(status, ptcode));
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc == 5 || argc == 6)
	{
		if (init_params(&data, argv+1) == 0)
			return (0);
		if (init_data(&data) == 1)
			return (0);
		init_dinner(&data);
		// init_eat(&data);
		clean(&data);
	}
	else
		error_msg("bad number of inputs\n");
	return (0);
}
