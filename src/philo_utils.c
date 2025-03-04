/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:28 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/04 18:43:46 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->n_philo)
	{
		philo = data->philos + i;
		handle_mtx(&philo->phil_mtx, DESTROY);
		i++;
	}
	handle_mtx(&data->mutx, DESTROY);
	handle_mtx(&data->print_mutx, DESTROY);
	free(data->forks);
	free(data->philos);
}

int	error_msg(const char *error)
{
	printf("%s\n", error);
	return (0);
}

int	have_max_eats(t_data *data, char *argv)
{
	if (control_errs(argv) == 1)
	{
		data->max_eats = ft_atol(argv);
		return (1);
	}
	error_msg("Error in param 6");
	return (0);
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

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
