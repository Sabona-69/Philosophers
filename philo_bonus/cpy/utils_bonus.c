/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:59:22 by hel-omra          #+#    #+#             */
/*   Updated: 2024/08/25 04:43:40 by hel-omra         ###   ########.fr       */
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
		sem_wait(philo->data->die);
		if (philo->data->sm1_died == TRUE)
		{
			sem_post(philo->data->die);
			return ;
		}
		sem_post(philo->data->die);
		usleep(100);
	}
}

// int	safe_malloc_mutex(t_params	*data)
// {
	
// 	return (0);
// }

int	freeing(char *message, int i, t_params *data)
{
	if (message)
		printf("%s\n", message);
	
	// free(data->fork);
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
