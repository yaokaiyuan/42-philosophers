/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 23:30:33 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/09/09 23:35:43 by ykai-yua         ###   ########.fr       */
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
			pthread_mutex_unlock(&data->mutex);
			print_died(&data->philos[i]);
			return (1);
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
	pthread_mutex_lock(&data->write);
	if (!data->dead)
	{
		printf("%lld %d died\n", get_time() - data->start_time, philo->id);
		data->dead = 1;
	}
	pthread_mutex_unlock(&data->write);
}

void	print_status(t_philo *philo, char *status)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->write);
	if (!data->dead)
		printf("%lld %d %s\n", get_time() - data->start_time,
			philo->id, status);
	pthread_mutex_unlock(&data->write);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
