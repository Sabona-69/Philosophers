/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:02:26 by hel-omra          #+#    #+#             */
/*   Updated: 2024/07/24 19:38:18 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->die);
	if (philo->data->sm1_died == TRUE)
	{
		pthread_mutex_unlock(&philo->data->die);
		return ;
	}
		printf("%ld\t %d %s\n", get_time() - philo->data->start,  philo->id, action);
	pthread_mutex_unlock(&philo->data->die);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;
	int i;
	philo = (t_philo *)arg;
	while (philo->data->sm1_died)
	{
		i = -1;
		while(++i < philo->data->n_philos)
		{
			pthread_mutex_lock(&philo->data->var);
			if (get_time() - philo->last_time_eat >= philo->data->time_to_die)
			{
			pthread_mutex_lock(&philo->data->die);
				if (philo->data->sm1_died == FALSE)
					printf("%ld\t %d %s\n", get_time() - philo[i].data->start,  philo[i].id, "die");
				philo->data->sm1_died = TRUE;
				pthread_mutex_unlock(&philo->data->die);
				pthread_mutex_unlock(&philo->data->var);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->data->var);
		}
	}
	return (NULL);
}

void	*routine(void	*var)
{
	t_philo *philo;

	philo = (t_philo *)var;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->data->die);
		if (philo->data->sm1_died == TRUE)
			return (pthread_mutex_unlock(&philo->data->die), NULL);
		pthread_mutex_unlock(&philo->data->die);
		pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
		print(philo, TAKING);
		pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
		print(philo, TAKING);
		pthread_mutex_lock(&philo->data->var);
		philo->last_time_eat = get_time(); 
		pthread_mutex_unlock(&philo->data->var);
		print(philo, EATING);
		pthread_mutex_lock(&philo->data->die);
		if (philo->data->sm1_died == TRUE)
		{
			pthread_mutex_unlock(&philo->data->die);
			ft_usleep(philo->data->time_to_eat);
			return NULL;
		}
		pthread_mutex_unlock(&philo->data->die);
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
		print(philo, SLEEPING);
		ft_usleep(philo->data->time_to_sleep);
		print(philo, THINKING);
	}
}

int	parse_it(char **s, t_params *data)
{
	int		i;

	data->n_philos = f_atoi(s[1]);
	data->time_to_die = f_atoi(s[2]);
	data->time_to_eat = f_atoi(s[3]);
	data->time_to_sleep = f_atoi(s[4]);
	pthread_mutex_init(&data->var, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->die, NULL);
	(s[5]) && (data->n_meals = f_atoi(s[5]));
	if (data->n_philos < 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->n_meals < 0)
		return (printf("Invalid arguments !\n"), -1);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (printf("malloc failed !\n"), -1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->fork)
	{
		free(data->philos);
		data->philos = NULL;
		return (printf("malloc failed !\n"), -1);
	}
	i = -1;
	data->start = get_time();
	data->sm1_died = FALSE;
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) == -1)
			return (printf("pthread_mutex_init failed\n"), -1);
		data->philos[i].meals_count = 0;
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->n_philos;
		data->philos[i].last_time_eat = get_time();
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].ph_thread, NULL, routine, &data->philos[i]) != 0)
			return (printf("Pthread create failed\n"), -1);
	}
	if (pthread_create(&data->mo_thread, NULL, monitoring, data->philos) != 0)
		return (printf("Pthread create failed\n"), -1);
	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->philos[i].ph_thread, NULL);
	pthread_detach(data->mo_thread);
	return (0);
}

int	main(int ac, char **av)
{
	t_params	*data;

	data = malloc(sizeof(t_params));
	if (!data)
		return (printf("malloc failed !\n"), 1);
	memset(data, 0, sizeof(t_params));
	if (ac > 6 || ac < 5)
		return (printf("Invalid arguments !\n"), 1);
	if (parse_it(av, data) == -1)
		return (1);
	free(data->fork);
	free(data->philos);
	free(data);
}
