/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:30:33 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/09/23 19:19:51 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	int			i;
	long long	current_time;

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
	return (data->dead);
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

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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
	data->dead = 1;
	pthread_mutex_unlock(&data->mutex);
	return (1);
}
