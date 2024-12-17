/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:42:03 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/17 16:38:41 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	start_simulation(t_data *data)
{
	int	i;

	data->start_time = get_time_in_ms() + (data->num_of_philos * 2 * 10);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&philosopher, data->philos[i]) != 0)
			return (error_failure("%s error:  cannot create thread.\n", NULL, data));
		i++;
	}
	if (data->num_of_philos > 1)
	{
		if (pthread_create(&data->monitor, NULL,
				&monitor, data) != 0)
			return (error_failure("%s error: cannot create thread.\n", NULL, data));
	}
	return (true);
}

static void	stop_simulation(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	if (data->num_of_philos > 1)
		pthread_join(data->monitor, NULL);
	destroy_mutexes(data);
	free_data(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (msg("incorrect input", NULL, EXIT_FAILURE));
	if (!is_valid_input(ac, av))
		return (EXIT_FAILURE);
	data = init_table(ac, av, 1);
	if (!data)
		return (EXIT_FAILURE);
	if (!start_simulation(data))
		return (EXIT_FAILURE);
	stop_simulation(data);
	return (EXIT_SUCCESS);
}
