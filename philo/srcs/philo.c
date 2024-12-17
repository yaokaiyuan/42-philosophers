/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:45:27 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/17 15:00:57 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	pthread_mutex_lock(&philo->data->forks[philo->fork[1]]);
	write_status(philo, false, GOT_FORK_2);
	write_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_eat = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->data, philo->data->time_to_eat);
	if (has_simulation_stopped(philo->data) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->eat_count += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[0]]);
	philo_sleep(philo->data, philo->data->time_to_sleep);
}

static void	think_routine(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->data->time_to_die
			- (get_time_in_ms() - philo->last_eat)
			- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		write_status(philo, false, THINKING);
	philo_sleep(philo->data, time_to_think);
}

static void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	philo_sleep(philo->data, philo->data->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->data->forks[philo->fork[0]]);
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->data->must_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_eat = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->data->start_time);
	if (philo->data->time_to_die == 0)
		return (NULL);
	if (philo->data->num_of_philos == 1)
		return (lone_philo_routine(philo));
	else if (philo->id % 2)
		think_routine(philo, true);
	while (has_simulation_stopped(philo->data) == false)
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
	}
	return (NULL);
}
