/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/24 01:00:57 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
◦ number_of_philosophers: es el número de filósofos, pero
	también el número de tenedores.

◦ time_to_die (en milisegundos): si un filósofo no empieza a comer en 
	time_to_die milisegundos desde el comienzo de su ultima comida 
	o desde el principio de la simulación, este morirá.

◦ time_to_eat (en milisegundos): es el tiempo que tiene un filósofo 
	para comer.
	Durante ese tiempo, tendrá los tenedores ocupados.

◦ time_to_sleep (en milisegundos): es el tiempo que tiene un filósofo 
	para dormir.

*******************    ARGUMENTO OPCIONAL    *******************
◦ number_of_times_each_philosopher_must_eat (ARGUMENTO OPCIONAL): si 
	todos los filósofos comen al menos 
	number_of_times_each_philosopher_must_eat veces,
	la simulación se detendrá. Si no se especifica, la simulación 
	se detendrá con la muerte de un filósofo
*/

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


int control_errs(char *str_num)
{
    long num;
    
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
	t_data data;

	if (argc == 5 || argc == 6)
	{
		if (init_params(&data, argv+1) == 0)
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
