/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:55:50 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/21 19:28:22 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(t_philo *philo, bool simulation)
{
	long	tm_eat;
	long	tm_sleep;
	long	tm_think;

	if (!simulation)
		write_status(THINKING, philo);
	if (philo->data->n_philo % 2 == 0)
		return ;
	tm_eat = philo->data->tm_eat;
	tm_sleep = philo->data->tm_sleep;
	tm_think = tm_eat * 2 - tm_sleep;
	if (tm_think < 0)
		tm_think = 0;
	percise_usleep(tm_think * 0.42, philo->data);
}

void	eat(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->first_fork->fork_id < philo->second_fork->fork_id)
	{
		first = philo->first_fork;
		second = philo->second_fork;
	}
	else
	{
		first = philo->second_fork;
		second = philo->first_fork;
	}
	handle_mtx(&first->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	handle_mtx(&second->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	write_status(EATING, philo);
	set_long(&philo->phil_mtx, &philo->last_eat, get_tm(MILISECOND));
	philo->eat_cnt++;
	percise_usleep(philo->data->tm_eat, philo->data);
	if (philo->data->max_eats > 0 && philo->eat_cnt == philo->data->max_eats)
		set_bool(&philo->phil_mtx, &philo->full, true);
	handle_mtx(&first->fork, UNLOCK);
	handle_mtx(&second->fork, UNLOCK);
}

bool	philo_die(t_philo *philo)
{
	long	elapsed;
	long	tm_to_die;

	if (get_bool(&philo->phil_mtx, &philo->full))
		return (false);
	elapsed = get_tm(MILISECOND) - get_long(&philo->phil_mtx, &philo->last_eat);
	tm_to_die = philo->data->tm_die / 1000;
	if (elapsed > tm_to_die)
		return (true);
	return (false);
}

void	get_fork(t_philo *philo, t_fork *fork, int pos)
{
	int	n_philos;

	n_philos = philo->data->n_philo;
	philo->first_fork = &fork[(pos + 1) % n_philos];
	philo->second_fork = &fork[pos];
	if (n_philos % 2)
	{
		philo->first_fork = &fork[pos];
		philo->second_fork = &fork[(pos + 1) % n_philos];
	}
}
