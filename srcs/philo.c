/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:12:49 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/09/09 23:54:12 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo, int first_fork, int second_fork)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[first_fork]);
	print_status(philo, "has taken a fork");
	if (check_death(data))
	{
		pthread_mutex_unlock(&data->forks[first_fork]);
		return ;
	}
	pthread_mutex_lock(&data->forks[second_fork]);
	print_status(philo, "has taken a fork");
	if (check_death(data))
	{
		pthread_mutex_unlock(&data->forks[first_fork]);
		pthread_mutex_unlock(&data->forks[second_fork]);
	}
}

static void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is eating");
	philo->last_eat = get_time();
	usleep(data->time_to_eat * 1000);
	philo->eat_count++;
}

void	eat(t_philo *philo)
{
	t_data	*data;
	int		first_fork;
	int		second_fork;

	data = philo->data;
	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	take_forks(philo, first_fork, second_fork);
	if (!check_death(data))
	{
		eating(philo);
		pthread_mutex_unlock(&data->forks[first_fork]);
		pthread_mutex_unlock(&data->forks[second_fork]);
	}
}

void	sleep_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	print_status(philo, "is thinking");
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->num_of_philos == 1)
	{
		print_status(philo, "has taken a fork");
		usleep(data->time_to_die * 1000);
		print_status(philo, "died");
		data->dead = 1;
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_death(data) && (data->must_eat == -1
			|| philo->eat_count < data->must_eat))
	{
		eat(philo);
		if (!check_death(data))
			sleep_think(philo);
	}
	return (NULL);
}
