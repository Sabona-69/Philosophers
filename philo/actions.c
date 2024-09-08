/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:04:36 by hel-omra          #+#    #+#             */
/*   Updated: 2024/09/08 01:03:30 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
	print(philo, TAKING);
	if (philo->data->n_philos == 1)
	{
		ft_usleep(philo->data->time_to_die, philo);
		pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
	print(philo, TAKING);
	pthread_mutex_lock(&philo->data->var);
	philo->last_time_eat = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->data->var);
	print(philo, EATING);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
}

void	print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->die);
	if (philo->data->sm1_died == TRUE)
	{
		pthread_mutex_unlock(&philo->data->die);
		return ;
	}
	printf("%ld\t %d %s\n", get_time() - philo->data->start, philo->id, action);
	pthread_mutex_unlock(&philo->data->die);
}

void	sleeping(t_philo *philo)
{
	print(philo, SLEEPING);
	ft_usleep(philo->data->time_to_sleep, philo);
}
