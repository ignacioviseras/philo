/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:56:01 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/17 22:19:58 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_philo
{
	int			*cnt;
	int			id;
	int			n_philo;
	int			tm_die;
	int			tm_eat;
	int			tm_sleep;
	pthread_mutex_t *mutx;
}			t_philo;

// FT_MALLOC
void				*ft_malloc(size_t size);

