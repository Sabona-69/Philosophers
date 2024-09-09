/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:59:22 by hel-omra          #+#    #+#             */
/*   Updated: 2024/09/09 04:14:03 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	freeing(char *message, t_params *data, int i)
{
	printf("%s\n", message);
	(sem_unlink("/forks"), sem_unlink("/write"), sem_unlink("/var"));
	while (i--)
		kill(data->philos[i].pid, SIGTERM);
	free(data->philos);
	free(data);
	exit(1);
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		sem_wait(philo->data->var);
		if (philo->data->sm1_died == TRUE)
		{
			sem_post(philo->data->var);
			return ;
		}
		sem_post(philo->data->var);
		usleep(100);
	}
}

int	f_atoi(char *s)
{
	long	res;

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
