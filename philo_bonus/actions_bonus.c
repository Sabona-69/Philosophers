/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 00:04:36 by hel-omra          #+#    #+#             */
/*   Updated: 2024/09/09 04:12:24 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philos)
{
	sem_wait(philos->data->forks);
	print(philos, TAKING);
	sem_wait(philos->data->forks);
	print(philos, TAKING);
	sem_wait(philos->data->var);
	philos->last_time_eat = get_time();
	philos->meals_count++;
	sem_post(philos->data->var);
	print(philos, EATING);
	ft_usleep(philos->data->time_to_eat, philos);
	sem_post(philos->data->forks);
	sem_post(philos->data->forks);
}

void	wait_for_all(t_params *data)
{
	int	i;
	int	status;
	int	exit_code;

	i = -1;
	status = 1;
	while (status > 0)
	{
		status = waitpid(-1, &exit_code, 0);
		if (WEXITSTATUS(exit_code))
			while (++i < data->n_philos)
				kill(data->philos[i].pid, SIGTERM);
	}
	return ;
}

void	print(t_philo *philo, char *action)
{
	sem_wait(philo->data->write);
	if (!ft_strcmp(action, "died"))
	{
		printf("%ld\t %d %s\n", get_time()
			- philo->data->start, philo->id, action);
		return ;
	}
	printf("%ld\t %d %s\n", get_time() - philo->data->start, philo->id, action);
	sem_post(philo->data->write);
}

void	sleeping(t_philo *philo)
{
	print(philo, SLEEPING);
	ft_usleep(philo->data->time_to_sleep, philo);
}
