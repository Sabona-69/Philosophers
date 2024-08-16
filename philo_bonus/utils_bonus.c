/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:59:22 by hel-omra          #+#    #+#             */
/*   Updated: 2024/08/16 18:01:14 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&philo->data->die);
		if (philo->data->sm1_died == TRUE)
		{
			pthread_mutex_unlock(&philo->data->die);
			return ;
		}
		pthread_mutex_unlock(&philo->data->die);
		usleep(100);
	}
}

int	safe_malloc_mutex(t_params	*data)
{
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->philos || !data->fork)
		return (freeing("malloc failed", 0, data), -1);
	if (pthread_mutex_init(&data->var, NULL))
		data->p_var = 1;
	if (pthread_mutex_init(&data->die, NULL))
		data->p_die = 1;
	if (pthread_mutex_init(&data->write, NULL))
		data->p_write = 1;
	if (data->p_var == 1 || data->p_die == 1 || data->p_write == 1)
		return (freeing("pthread_mutex_init failed", 0, data), -1);
	return (0);
}

int	freeing(char *message, int i, t_params *data)
{
	if (message)
		printf("%s\n", message);
	while (i--)
		pthread_mutex_destroy(&data->fork[i]);
	if (data->p_die == 1)
		pthread_mutex_destroy(&data->var);
	if (data->p_write == 1)
		pthread_mutex_destroy(&data->write);
	free(data->fork);
	free(data->philos);
	free(data);
	return (-1);
}

int	f_atoi(char *s)
{
	long		res;

	res = 0;
	while (*s && (*s == 32 || (*s <= 9 && *s >= 13)))
		s++;
	if (*s == '\0')
		return (-1);
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			return (-1);
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - '0';
		s++;
		if (res > 2147483647)
			return (-1);
	}
	while (*s && (*s == 32 || (*s <= 9 && *s >= 13)))
		s++;
	if (*s != '\0' || res == 0)
		return (-1);
	return (res);
}
