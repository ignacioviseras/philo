/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:32 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/24 17:35:14 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
	if the return is -1 the flag error
*/
long  get_tm(t_time time_e)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		error_msg("gettime failed");
	if (SECOND == time_e)
		return (time.tv_sec + (time.tv_usec / 1000000));
	else if (MILISECOND == time_e)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	else if (MICROSECOND == time_e)
		return ((time.tv_sec * 1000000) + time.tv_usec);
	else
		error_msg("Wrong in get_tm");
	return (-1);
}

void percise_usleep(long usec, t_data *data)
{
	long start;
	long elapsed;
	long rem;

	start = get_tm(MICROSECOND);
	while (get_tm(MICROSECOND) - start < usec)
	{
		if (simulation_finish(data))
			break;
		elapsed = get_tm(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem /2);//fixed por bug
		else
			while (get_tm(MICROSECOND)- start < usec);
			
	}
	
}

// void log_state(t_philo *philo, char *state)
// {
// 	pthread_mutex_lock(&philo->data->print_mutx);
// 	if (!philo->data->finish)
//         printf("id '%d' state '%s' %d\n", philo->id, state, get_timestamp() - philo->data->init_time);
//     pthread_mutex_unlock(&philo->data->print_mutx);
	
// }

