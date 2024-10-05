/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:12:49 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/10/05 08:01:58 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
	}
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
	ft_msleep(data->time_to_eat);
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
