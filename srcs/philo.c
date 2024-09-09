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

static void	take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
}

static void	release_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
}

static void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is eating");
	pthread_mutex_lock(&data->mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&data->mutex);
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&data->mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&data->mutex);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	eating(philo);
	release_forks(philo);
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
		ft_usleep(data->time_to_die);
		print_status(philo, "died");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(data->time_to_eat / 2);
	while (!check_death(data) && (data->must_eat == -1
			|| philo->eat_count < data->must_eat))
	{
		eat(philo);
		if (!check_death(data))
			sleep_think(philo);
	}
	return (NULL);
}
