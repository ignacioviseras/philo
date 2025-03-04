/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:32 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/04 18:44:25 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_tm(t_time time_e)
{
	struct timeval	time;

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

void	percise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_tm(MICROSECOND);
	while (get_tm(MICROSECOND) - start < usec)
	{
		if (simulation_finish(data))
			break ;
		elapsed = get_tm(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
			while (get_tm(MICROSECOND) - start < usec)
				;
	}
}
