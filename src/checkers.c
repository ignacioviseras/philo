/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:58:48 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/24 01:00:09 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool simulation_finish(t_data *data)
{
    return (get_bool(&data->mutx, &data->end_time));
}

/*
	its a while to wait all the threads 
*/
void wait_all(t_data *data)
{
    while (!get_bool(&data->mutx, &data->threads_ready));
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