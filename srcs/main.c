/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:12:40 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/10/05 12:23:58 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->num_of_philos == 1)
	{
		take_fork_and_die(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_msleep(data->time_to_eat / 2);
	while (1)
	{
		if (!check_death(data) && (data->must_eat == -1 || !check_full(data)))
			eat(philo);
		if (!check_death(data) && (data->must_eat == -1 || !check_full(data)))
			sleepna(philo);
		if (!check_death(data) && (data->must_eat == -1 || !check_full(data)))
			think(philo);
		else
			break ;
	}
	return (NULL);
}

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
	pthread_mutex_destroy(&data->mutex);
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
	join_threads(&data);
	cleanup(&data);
	return (0);
}
