/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:02:26 by hel-omra          #+#    #+#             */
/*   Updated: 2024/08/25 04:50:02 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse_it(char **s, t_params *data)
{
	data->n_philos = f_atoi(s[1]);
	data->time_to_die = f_atoi(s[2]);
	data->time_to_eat = f_atoi(s[3]);
	data->time_to_sleep = f_atoi(s[4]);
	(s[5]) && (data->n_meals = f_atoi(s[5]));
	if (data->n_philos < 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->n_meals < 0)
		return (-1);
	sem_unlink("/tmp/.forks");
	sem_unlink("/tmp/.write");
	sem_unlink("/tmp/.die");
	data->forks = sem_open("/tmp/.fork", O_CREAT, 0644, data->n_philos);
	// if (data->forks == SEM_FAILED)
	// 	printerror(data);
	data->write = sem_open("/tmp/.write", O_CREAT, 0644, 1);
	// if (data->write == SEM_FAILED)
	// 	printerror(data);
	data->die = sem_open("/tmp/.die", O_CREAT, 0644, 1);
	// if (data->die == SEM_FAILED)
	// 	printerror(data);
	return (0);
}

int	monitoring(t_philo *philo)
{
	int		i;

	while (philo->data->sm1_died)
	{
		i = -1;
		while (++i < philo->data->n_philos)
		{
			sem_wait(philo->data->var);
			if (get_time() - philo->last_time_eat >= philo->data->time_to_die)
			{
				sem_wait(philo->data->die);
				if (philo->data->sm1_died == FALSE)
					printf("%ld\t %d %s\n", get_time() - philo[i].data->start,
						philo[i].id, "died");
				philo->data->sm1_died = TRUE;
				sem_post(philo->data->die);
				return (sem_post(philo->data->var), exit(1), 0);
			}
			else if (philo->meals_count >= philo->data->n_meals
				&& philo->data->n_meals)
				return (sem_post(philo->data->var), 0);
			sem_post(philo->data->var);
		}
	}
	return (0);
}

void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	while (1)
	{
		sem_wait(philo->data->die);
		if (philo->data->sm1_died == TRUE || (philo->meals_count
				>= philo->data->n_meals && philo->data->n_meals))
			break ;
		sem_post(philo->data->die);
		eating(philo);
		sleeping(philo);
		print(philo, THINKING);
	}
	exit (0);
}

int	init_it(t_params *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	data->fork_pid = malloc(sizeof(int) * data->n_philos);
	if (!data->philos || !data->fork_pid)
		return (freeing("malloc failed", 0, data), -1);
	(1) && (i = -1, data->sm1_died = FALSE, data->start = get_time());
	while (++i < data->n_philos)
	{
		data->philos[i].meals_count = 0;
		data->philos[i].id = i + 1;
		data->philos[i].last_time_eat = get_time();
		data->philos[i].data = data;
		data->fork_pid[i] = fork();
		if (data->fork_pid[i] == -1)
			return (freeing("fork() failed", 0, data), -1);
		if (data->fork_pid[i] == 0)
			routine(data->philos);

	}
	monitoring(data->philos);
	return (0);
}

void	waitfpid(t_philo *philos)
{
	int	i;
	int	status;

	i = 0;
	while (i < philos->data->n_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && status)
		{
			i = 0;
			while (i < philos->data->n_philos)
				kill(philos->data->fork_pid[i++], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(philos->data->forks);
	sem_close(philos->data->write);
	sem_close(philos->data->die);
	sem_unlink("/tmp/.fork");
	sem_unlink("/tmp/.die");
	sem_unlink("/tmp/.write");
	free(philos->data->fork_pid);
	free(philos->data);
	free(philos);
	// destroy_free(philos);
}


int	main(int ac, char **av)
{
	t_params	*data;

	if (ac > 6 || ac < 5)
		return (printf("Invalid arguments !\n"), 1);
	data = malloc(sizeof(t_params));
	if (!data)
		(printf("malloc failed !\n"), exit(1));
	memset(data, 0, sizeof(t_params));
	if (parse_it(av, data) == -1)
		return (freeing("Invalid arguments !", 0, data), 1);
	if (init_it(data) == -1)
		return (1);
	// freeing(NULL, data->n_philos, data);
}
