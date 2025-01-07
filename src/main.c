/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/17 22:03:49 by igvisera         ###   ########.fr       */
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

// void *text_thread(void *data)
// {
// 	char *txt;

// 	txt = (char *) data;
// 	printf("%s\n", txt);
// 	return NULL;
// }

// int	main(int argc, char **argv)
// {
// 	pthread_t thread1;
// 	pthread_t thread2;
// 	// int result;

// 	printf("nº de argc '%d'\n", argc);
// 	printf("param argv '%s'\n", argv[0]);
// 	if (argc == 5)
// 	{
// 		// result = pthread_create(&thread1, NULL, hello_thread, NULL);
// 		pthread_create(&thread1, NULL, &text_thread, "hola");
// 		pthread_create(&thread2, NULL, &text_thread, "adios");
// 		// if (result != 0)
// 		// {
// 		// 	perror("Error al crear el hilo");
// 		// 	return (1);
// 		// }
// 		pthread_join(thread1, NULL);
// 		pthread_join(thread2, NULL);
// 	}
// 	return (0);
// }

// void	*increment_counter(void *philo)
// {

// }

void *text_thread(void *data)
{
	char *txt;

	txt = (char *) data;
	printf("%s\n", txt);
	return NULL;
}

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

void	error(char *str)
{
	printf("\t------ Error ------\n%s\n", str);
	return;
}

int	control_errs(char *str_num)
{
	long num;
	
	num = ft_atol(str_num);
	if (num < 0 || num < INT_MIN || num > INT_MAX)
	{
		error("Only unsigned int numbers can be used");
		return (0);
	}
	return (1);// num ok
}

int init_params(t_philo *philo, char **argv)
{
	int x;
	x = 0;
	printf("dato en 0 '%s'\n", argv[0]);
	while (x < 4)
	{	
		if (control_errs(argv[x]) == 0)
			return (0);
		x++;
	}
	philo->n_philo = ft_atol(argv[0]);
	philo->tm_die = ft_atol(argv[1]);
	philo->tm_eat = ft_atol(argv[2]);
	philo->tm_sleep = ft_atol(argv[3]);
	return (1);
}

int	main(int argc, char **argv)
{
	printf("nº de argc '%d'\n", argc);
	if (argc == 5)
	{
		t_philo philo;
		if (init_params(&philo, argv+1) == 0)
			return (0);
		printf("philo->n_philo  '%d'\n", philo.n_philo);
		printf("philo->tm_die   '%d'\n", philo.tm_die);
		printf("philo->tm_eat   '%d'\n", philo.tm_eat);
		printf("philo->tm_sleep '%d'\n", philo.tm_sleep);
		if (argc == 7)
		{

			philo.cnt = 0;
			pthread_mutex_init(&philo.mutx, NULL);

			pthread_t threads[philo.n_philo];
			pthread_create(&threads[0], NULL, &text_thread, "hola");
		}
	}
	return (0);
}
