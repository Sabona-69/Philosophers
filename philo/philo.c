/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:02:26 by hel-omra          #+#    #+#             */
/*   Updated: 2024/09/16 08:42:50 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (0);
}

int	monitoring(t_philo *philo)
{
	int		i;

	while (1)
	{
		(1) && (i = -1, philo->data->philo_full = 0);
		while (++i < philo->data->n_philos)
		{
			pthread_mutex_lock(&philo->data->var);
			if (get_time() - philo[i].last_time_eat
				>= philo->data->time_to_die)
			{
				pthread_mutex_lock(&philo->data->die);
				if (philo->data->sm1_died == FALSE)
					printf("%ld\t %d %s\n", get_time() - philo[i].data->start,
						philo[i].id, "died");
				philo->data->sm1_died = TRUE;
				pthread_mutex_unlock(&philo->data->die);
				return (pthread_mutex_unlock(&philo->data->var), 0);
			}
			if (!check_meals(&philo[i]))
				return (pthread_mutex_unlock(&philo->data->var), 0);
			pthread_mutex_unlock(&philo->data->var);
		}
	}
	return (0);
}

void	*routine(void	*var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->die);
		if (philo->data->sm1_died == TRUE || (philo->meals_count
				>= philo->data->n_meals && philo->data->n_meals))
			return (pthread_mutex_unlock(&philo->data->die), NULL);
		pthread_mutex_unlock(&philo->data->die);
		eating(philo);
		sleeping(philo);
		print(philo, THINKING);
	}
}

int	init_it(t_params *data)
{
	int	i;

	if (safe_malloc_mutex(data) == -1)
		return (-1);
	(1) && (i = -1, data->sm1_died = FALSE, data->start = get_time());
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) == -1)
			return (freeing("pthread_mutex_init failed", i, data), -1);
		data->philos[i].meals_count = 0;
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = (i + 1) % data->n_philos;
		data->philos[i].last_time_eat = get_time();
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].ph_thread
				, NULL, routine, &data->philos[i]) < 0)
			return (freeing("mutex_init failed", data->n_philos, data), -1);
	}
	monitoring(data->philos);
	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->philos[i].ph_thread, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_params	*data;

	if (ac > 6 || ac < 5)
		return (printf("Invalid arguments !\n"), 1);
	data = malloc(sizeof(t_params));
	if (!data)
		return (printf("malloc failed !\n"), 1);
	memset(data, 0, sizeof(t_params));
	if (parse_it(av, data) == -1)
		return (freeing("Invalid arguments !", 0, data), 1);
	if (init_it(data) == -1)
		return (1);
	freeing(NULL, data->n_philos, data);
}
