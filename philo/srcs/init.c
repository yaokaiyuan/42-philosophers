/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:40:57 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/23 15:40:21 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!forks)
		return (error_null("%s error: cannot allocate memory.\n", NULL, 0));
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (error_null("%s error: cannot allocate memory.\n", NULL, 0));
		i++;
	}
	return (forks);
}

static void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->data->num_of_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->data->num_of_philos;
		philo->fork[1] = philo->id;
	}
}

static t_philo	**init_philosophers(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!philos)
		return (error_null("%s error: cannot allocate memory.\n", NULL, 0));
	i = 0;
	while (i < data->num_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (error_null("%s error: cannot allocate memory.\n", NULL, 0));
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
			return (error_null("%s error: cannot create mutex.\n", NULL, 0));
		philos[i]->data = data;
		philos[i]->id = i;
		philos[i]->eat_count = 0;
		philos[i]->last_eat = get_time_in_ms();
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

static bool	init_global_mutexes(t_data *data)
{
	data->forks = init_forks(data);
	if (!data->forks)
		return (false);
	if (pthread_mutex_init(&data->stop_lock, 0) != 0)
		return (error_failure("%s error: cannot create mutex.\n", NULL, data));
	if (pthread_mutex_init(&data->write, 0) != 0)
		return (error_failure("%s error: cannot create mutex.\n", NULL, data));
	return (true);
}

t_data	*init_table(int ac, char **av, int i)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (error_null("%s error: cannot allocate memory.\n", NULL, 0));
	data->num_of_philos = integer_atoi(av[i++]);
	data->time_to_die = integer_atoi(av[i++]);
	data->time_to_eat = integer_atoi(av[i++]);
	data->time_to_sleep = integer_atoi(av[i++]);
	data->must_eat = -1;
	if (ac - 1 == 5)
		data->must_eat = integer_atoi(av[i]);
	data->philos = init_philosophers(data);
	if (!data->philos)
		return (NULL);
	if (!init_global_mutexes(data))
		return (NULL);
	data->stop_time = false;
	return (data);
}
