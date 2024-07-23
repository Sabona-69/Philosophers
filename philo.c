/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:02:26 by hel-omra          #+#    #+#             */
/*   Updated: 2024/07/23 18:12:47 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print(t_params *data)
{
	printf("=============================================\n");
	printf("number of meals == [%d]\n", data->n_meals);
	printf("number of philos == [%d]\n", data->n_philos);
	printf("time to die == [%ld]\n", data->time_to_die);
	printf("time to eat == [%ld]\n", data->time_to_eat);
	printf("time to sleep == [%ld]\n", data->time_to_sleep);
	printf("time to sleep == [%ld]\n", data->time_to_sleep);
	printf("=============================================\n");
	int i = -1;
	while (++i < data->n_philos)
	{
		printf("=============================================\n");
		if (data->philos[i].died == FALSE)
			printf("is he died ? == FALSE\n");
		else if (data->philos[i].died == TRUE)
			printf("is he died ? == TRUE\n");
		printf("r_fork == [%d]\n", data->philos[i].l_fork);
		printf("l_fork == [%d]\n", data->philos[i].r_fork);
		printf("Id of philo == [%d]\n", data->philos[i].id);
		printf("meals counter == [%d]\n", data->philos[i].meals_count);
		printf("=============================================\n");
	}	
}

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
	pthread_mutex_lock(&philo->data->write);
	printf("%ld\t %d %s\n", get_time() - philo->data->start,  philo->id, action);
	pthread_mutex_unlock(&philo->data->write);
}

void	*monitoring(void	*var)
{
	t_philo *philo;

	philo = (t_philo *)var;
	if (philo->last_time_eat - get_time() > philo->data->time_to_eat)
	{
		pthe
	}
}

void	*routine(void	*var)
{
	t_philo *philo;

	philo = (t_philo *)var;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
		print(philo, TAKING);
		pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
		print(philo, TAKING);
		pthread_mutex_lock(&philo->data->var);
		philo->last_time_eat = get_time(); // write
		pthread_mutex_unlock(&philo->data->var);
		print(philo, EATING);
		ft_usleep(philo->data->time_to_eat);
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

	i = -1;
	data->n_philos = f_atoi(s[1]);
	data->time_to_die = f_atoi(s[2]);
	data->time_to_eat = f_atoi(s[3]);
	data->time_to_sleep = f_atoi(s[4]);
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
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) == -1)
			return (printf("pthread_mutex_init failed\n"), -1);
		data->philos[i].died = FALSE;
		data->philos[i].meals_count = 0;
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->n_philos;
		data->philos[i].last_time_eat = get_time();
		data->philos[i].data = data;
		if (pthread_create(&data->philos->philo, NULL, routine, &data->philos[i]) != 0)
			return (printf("Pthread create failed\n"), -1);
	}
	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->philos[i].philo, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_params	*data;

	// atexit(f);
	data = malloc(sizeof(t_params));
	if (!data)
		return (printf("malloc failed !\n"), -1);
	memset(data, 0, sizeof(t_params));
	if (ac > 6 || ac < 5)
		return (printf("Invalid arguments !\n"), 1);
	if (parse_it(av, data) == -1 )
		return (1);
	// if (start_simulation(data) == -1)
	// 	return (1);
	free(data->fork);
	free(data->philos);
	free(data);
	// printf("%ld", get_time());
}
