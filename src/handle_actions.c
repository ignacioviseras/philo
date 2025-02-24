/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:39:58 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/24 00:43:56 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
if the int returned is 0 its al ok
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
int thread_errors(int status, t_ptcode pt_code)
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

/*
if the int returned is 0 its al ok
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
int mtx_errors(int status, t_ptcode pt_code)
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
