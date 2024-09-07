/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:02:26 by hel-omra          #+#    #+#             */
/*   Updated: 2024/09/07 01:00:03 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void parse_it(char **s, t_params *data)
{
	data->n_philos = f_atoi(s[1]);
	data->time_to_die = f_atoi(s[2]);
	data->time_to_eat = f_atoi(s[3]);
	data->time_to_sleep = f_atoi(s[4]);
	(s[5]) && (data->n_meals = f_atoi(s[5]));
	if (data->n_philos < 0 || data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0 || data->n_meals < 0)
		(free(data), printf("Invalid args !\n"), exit(1));
	(sem_unlink("/forks"), sem_unlink("/write"), sem_unlink("/var"));
	data->forks = sem_open("/forks", O_CREAT, 0644, data->n_philos);
	data->write = sem_open("/write", O_CREAT, 0644, 1);
	data->var = sem_open("/var", O_CREAT, 0644, 1);
	if (data->forks < 0 || data->write < 0 || data->var < 0)
	{
		(sem_unlink("/forks"), sem_unlink("/write"), sem_unlink("/var"));
		(free(data), printf("sem_open failed !\n"), exit(1));
	}
}

void *monitoring(void *arg)
{
	t_philo *philo;
	int i;

	philo = arg;
	while (1)
	{
		sem_wait(philo->data->var);
		if (get_time() - philo->last_time_eat >= philo->data->time_to_die)
		{
			if (philo->data->sm1_died == FALSE)
				printf("%ld\t %d %s\n", get_time() - philo->data->start,
						philo->id, "died");
			philo->data->sm1_died = TRUE;
			return (exit(1), NULL);
		}	
		else if (philo->meals_count >= philo->data->n_meals && philo->data->n_meals)
			return (sem_post(philo->data->var), NULL);
		sem_post(philo->data->var);
	}
	return (NULL);
}

void routine(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, monitoring, philo) < 0)
		freeing("pthread_create failed", philo->data, philo->data->n_philos);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	while (1)
	{
		sem_wait(philo->data->var);
		if (philo->data->sm1_died == TRUE || (philo->meals_count >= philo->data->n_meals && philo->data->n_meals))
			exit(1);
		sem_post(philo->data->var);
		eating(philo);
		sleeping(philo);
		print(philo, THINKING);
	}
	pthread_join(philo->thread, NULL);
	exit(0);
}

int init_it(t_params *data)
{
	int i;
	int pid;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	(1) && (i = -1, data->sm1_died = FALSE, data->start = get_time());
	while (++i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_count = 0;
		data->philos[i].data = data;
		data->philos[i].last_time_eat = get_time();
	}
	i = -1;
	while (++i < data->n_philos)
	{
		pid = fork();
		if (pid == -1)
			freeing("fork() failed", data, i);
		if (pid == 0)
			routine(&data->philos[i]);
		else
			data->philos[i].pid = pid;
	}
	return (pid);
}

void wait_for_all(t_params *data)
{
	int i;
	int status;
	int exit_code;

	i = -1;
	status = 1;
	while (status > 0)
	{
		status = waitpid(-1, &exit_code, 0);
		if (WEXITSTATUS(exit_code))
			while (++i < data->n_philos)
				kill(data->philos[i].pid, SIGTERM);
	}
	return;
}

int main(int ac, char **av)
{
	t_params *data;

	if (ac > 6 || ac < 5)
		return (printf("Invalid arguments !\n"), 1);
	data = malloc(sizeof(t_params));
	if (!data)
		(printf("malloc failed !\n"), exit(1));
	memset(data, 0, sizeof(t_params));
	parse_it(av, data);
	int pid = init_it(data);
	if (pid != 0)
		wait_for_all(data);
	return (1);
}
