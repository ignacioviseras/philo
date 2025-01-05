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

void *text_thread(void *data)
{
	char *txt;

	txt = (char *) data;
	printf("%s\n", txt);
	return NULL;
}

int	main(int argc, char **argv)
{
	pthread_t thread1;
	pthread_t thread2;
	// int result;

	printf("nº de argc '%d'\n", argc);
	printf("param argv '%s'\n", argv[0]);
	if (argc == 5)
	{
		// result = pthread_create(&thread1, NULL, hello_thread, NULL);
		pthread_create(&thread1, NULL, &text_thread, "hola");
		pthread_create(&thread2, NULL, &text_thread, "adios");
		// if (result != 0)
		// {
		// 	perror("Error al crear el hilo");
		// 	return (1);
		// }
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
	}
	return (0);
}
