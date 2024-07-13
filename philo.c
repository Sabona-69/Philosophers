/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-omra <hel-omra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:02:26 by hel-omra          #+#    #+#             */
/*   Updated: 2024/07/13 07:58:32 by hel-omra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	parse_init_it(char **s, t_params *data)
{
	int		i;

	(1) && (i = -1, data->n_philos = f_atoi(s[1]));
	(1) && (data->time_to_die = f_atoi(s[2]), data->time_to_eat = f_atoi(s[3]));
	data->time_to_sleep = f_atoi(s[4]);
	(s[5] != NULL) && (data->n_meals = f_atoi(s[5]));
	if (data->n_philos < 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->n_meals < 0)
		return (printf("Invalid arguments !\n"), -1);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks || !data->philos)
		return (printf("malloc failed !\n"), -1);
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) == -1)
			return (printf("pthread_mutex_init failed\n"), -1);
		(1) && (data->forks[i].id = i, data->philos[i].id = i + 1);
		(1) && (data->philos[i].died = FALSE, data->philos[i].meals_count = 0);
		data->philos[i].r_fork->id = i;
		data->philos[i].l_fork->id = (i + 1) % data->n_philos;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_params	data;

	if (ac > 6 || ac < 5)
		return (printf("Invalid arguments !\n"), 1);
	if (parse_init_it(av, &data) == -1)
		return (1);
}
