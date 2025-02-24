/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 01:00:27 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/24 01:00:51 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
        if (philo->full)
            break;
        eat(philo);
        write_status(SLEEPING, philo);
        percise_usleep(philo->data->tm_sleep, philo->data);
        thinking(philo, false);
    }
    return (NULL);
}

void *monitor_dinner(void *tdata)
{
    t_data *data;
    int i;

    data = (t_data *)tdata;
    while (!thread_running(&data->mutx, &data->n_threads_running, data->n_philo));
    while (!simulation_finish(data))
    {
        i = 0;
        while (i < data->n_philo && !simulation_finish(data))
        {
            if (philo_die(data->philos + i))
            {
                set_bool(&data->mutx, &data->end_time, true);
                write_status(DIED, data->philos + i);
            }
            i++;
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