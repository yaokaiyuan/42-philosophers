/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:12:27 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/09/09 23:05:57 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (1);
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->write, NULL)
		|| pthread_mutex_init(&data->mutex, NULL))
		return (1);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (1);
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_of_philos;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat = get_time();
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	data->num_of_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = atoi(argv[5]);
	data->dead = 0;
	data->start_time = get_time();
	if (init_mutexes(data) || init_philos(data))
		return (1);
	return (0);
}
