/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:52:44 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/24 00:54:30 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_dinner(t_data *data)
{
    int i;

    i = 0;
    if (data->max_eats == 0)
        return;
    else if (data->n_philo == 1)
        handle_thread(&data->philos[0].thread_id, one_philo, &data->philos[0], CREATE);
    else
    {
        while (i < data->n_philo)
        {
            handle_thread(&data->philos[i].thread_id, dinner_simulat, &data->philos[i], CREATE);
            i++;
        }
    }
    handle_thread(&data->monitor, monitor_dinner, data, CREATE);
    data->init_time = get_tm(MILISECOND);
    set_bool(&data->mutx, &data->threads_ready, true);
    i = 0;
    while (i < data->n_philo)
    {
        handle_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }
    set_bool(&data->mutx, &data->end_time, true);
    handle_thread(&data->monitor, NULL, NULL, JOIN);
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
    if (data->tm_die < 60000 || data->tm_eat < 60000 || data->tm_sleep < 60000)
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

void init_philo(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i < data->n_philo)
    {
        philo = data->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->eat_cnt = 0;
        philo->data = data;
        handle_mtx(&philo->phil_mtx, INIT);
        get_fork(philo, data->forks, i);
        i++;
    }
}

int init_data(t_data *data)
{
    int i;

    i = 0;
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
    while (i < data->n_philo)
    {
        handle_mtx(&data->forks[i].fork, INIT);
        data->forks[i].fork_id = i;
        i++;
    }
    init_philo(data);
    return (1);
}
