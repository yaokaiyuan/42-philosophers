/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:30:33 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/10/05 11:55:12 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_already_dead(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex);
	return (0);
}

int	check_death(t_data *data)
{
	int			i;
	long long	current_time;

	if (check_already_dead(data))
		return (1);
	pthread_mutex_lock(&data->mutex);
	current_time = get_time();
	i = 0;
	while (i < data->num_of_philos)
	{
		if (current_time - data->philos[i].last_eat > data->time_to_die)
		{
			if (!data->dead)
			{
				data->dead = 1;
				print_died(&data->philos[i]);
				return (1);
			}
		}
		i++;
	}
	pthread_mutex_unlock(&data->mutex);
	return (0);
}

void	print_died(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	printf("%lld %d died\n", get_time() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->mutex);
}

void	print_status(t_philo *philo, char *status)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->mutex);
	if (!data->dead)
		printf("%lld %d %s\n", get_time() - data->start_time,
			philo->id, status);
	pthread_mutex_unlock(&data->mutex);
}

int	check_full(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->mutex);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philos[i].eat_count < data->must_eat)
		{
			pthread_mutex_unlock(&data->mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&data->mutex);
	return (1);
}
