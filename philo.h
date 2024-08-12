/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:19:09 by hel-omra          #+#    #+#             */
/*   Updated: 2024/08/12 18:27:14 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h> 	
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

# define TAKING "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

# define FALSE 1
# define TRUE 0

typedef struct s_params t_params;

typedef struct s_philo
{
	pthread_t		ph_thread;
	int				id;
	long			last_time_eat;
	int				meals_count;
	int				l_fork;
	int				r_fork;
	t_params		*data;
}	t_philo;

typedef struct s_params
{
	pthread_t		mo_thread;
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_meals;
	size_t			start;
	int				sm1_died;
	pthread_mutex_t	*fork;
	pthread_mutex_t	die;
	pthread_mutex_t	var;
	pthread_mutex_t write;
	t_philo			*philos;
}	t_params;

int		f_atoi(char *s);

#endif
