/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:28 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/20 17:58:29 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
