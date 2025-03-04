/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/04 18:41:22 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	long	num;

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
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (init_params(&data, argv + 1) == 0)
			return (0);
		if (init_data(&data) == 0)
			return (0);
		init_dinner(&data);
		clean(&data);
	}
	else
		error_msg("bad number of inputs\n");
	return (0);
}
