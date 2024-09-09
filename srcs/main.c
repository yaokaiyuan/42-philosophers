/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:12:40 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/09/09 23:24:01 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher, &data->philos[i]))
		{
			printf("Couldn't build threads\n");
			return ;
		}
		i++;
	}
	return ;
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			printf("Error joining thread %d\n", i);
		i++;
	}
}

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong arguements\n");
		return (1);
	}
	if (init(&data, argc, argv))
		return (1);
	create_threads(&data);
	while (!data.dead)
	{
		if (check_death(&data))
			break ;
		usleep(1000);
	}
	join_threads(&data);
	cleanup(&data);
	return (0);
}
