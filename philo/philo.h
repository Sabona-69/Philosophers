/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:19:09 by hel-omra          #+#    #+#             */
/*   Updated: 2024/09/08 07:05:07 by alaassir         ###   ########.fr       */
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
# include <stdbool.h>

# define TAKING "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

# define FALSE 1
# define TRUE 0

typedef struct s_params	t_params;

typedef struct s_philo
{
	pthread_t		ph_thread;
	int				id;
	long			last_time_eat;
	int				meals_count;
	int				l_fork;
	int				r_fork;
	bool			full;
	t_params		*data;
}	t_philo;

typedef struct s_params
{
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
	pthread_mutex_t	write;
	int				p_die;
	int				p_var;
	int				p_write;
	t_philo			*philos;
}	t_params;

int		f_atoi(char *s);
int		safe_malloc_mutex(t_params	*data);
void	ft_usleep(size_t milliseconds, t_philo *philo);
int		freeing(char *message, int i, t_params *data);
void	print(t_philo *philo, char *action);
size_t	get_time(void);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);

#endif
