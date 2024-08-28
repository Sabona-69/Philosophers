/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:19:09 by hel-omra          #+#    #+#             */
/*   Updated: 2024/08/25 04:47:20 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <sys/time.h> 	
# include <semaphore.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# define TAKING "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"

# define FALSE 1
# define TRUE 0

typedef struct s_params	t_params;

typedef struct s_philo
{
	// pthread_t		ph_thread;
	int				id;
	int				meals_count;
	long			last_time_eat;
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
	int				*fork_pid;
	sem_t			*forks;
	sem_t			*die;
	sem_t			*var;
	sem_t			*write;
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