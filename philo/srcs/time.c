/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:46:43 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/17 12:48:03 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_sleep(t_data *data, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (has_simulation_stopped(data))
			break ;
		usleep(100);
	}
}

void	sim_start_delay(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}
