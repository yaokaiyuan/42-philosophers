/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:39:48 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/17 16:40:14 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_sim_stop_flag(t_data *data, bool state)
{
	pthread_mutex_lock(&data->stop_lock);
		data->stop_time = state;
	pthread_mutex_unlock(&data->stop_lock);
}

bool	has_simulation_stopped(t_data *data)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&data->stop_lock);
	if (data->stop_time == true)
		r = true;
	pthread_mutex_unlock(&data->stop_lock);
	return (r);
}

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_eat) >= philo->data->time_to_die)
	{
		set_sim_stop_flag(philo->data, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

static bool	end_condition_reached(t_data *data)
{
	int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->philos[i]->meal_time_lock);
		if (kill_philo(data->philos[i]))
			return (true);
		if (data->must_eat != -1)
			if (data->philos[i]->eat_count
				< data->must_eat)
				all_ate_enough = false;
		pthread_mutex_unlock(&data->philos[i]->meal_time_lock);
		i++;
	}
	if (data->must_eat != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(data, true);
		return (true);
	}
	return (false);
}

void	*monitor(void *input)
{
	t_data			*data;

	data = (t_data *)input;
	if (data->must_eat == 0)
		return (NULL);
	set_sim_stop_flag(data, false);
	sim_start_delay(data->start_time);
	while (true)
	{
		if (end_condition_reached(data) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
