/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:38:31 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/17 16:39:37 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_data(t_data *data)
{
	int	i;

	if (!data)
		return (NULL);
	if (data->forks != NULL)
		free(data->forks);
	if (data->philos != NULL)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (data->philos[i] != NULL)
				free(data->philos[i]);
			i++;
		}
		free(data->philos);
	}
	free(data);
	return (NULL);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->stop_lock);
}

int	msg(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf(str, "philo:");
	else
		printf(str, "philo:", detail);
	return (exit_no);
}

int	error_failure(char *str, char *details, t_data *data)
{
	if (data != NULL)
		free_data(data);
	return (msg(str, details, 0));
}

void	*error_null(char *str, char *details, t_data *data)
{
	if (data != NULL)
		free_data(data);
	msg(str, details, EXIT_FAILURE);
	return (NULL);
}