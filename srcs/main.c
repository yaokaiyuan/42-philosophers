/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:12:40 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/09/09 22:31:20 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 5 && argc != 6)
    {
        printf("Wrong arguements\n");
        return (1);
    }
    if (init(&data, argc, argv))
        return (1);
    // 创建哲学家线程(out while loop)
    for (int i = 0; i < data.num_of_philos; i++)
    {
        if (pthread_create(&data.philos[i].thread, NULL, philosopher, &data.philos[i]))
        {
            printf("Couldn't build threads\n");
            return (1);
        }
    }
    // 检查死亡情况
    while (!data.dead)
    {
        if (check_death(&data))
    		break;
    	usleep(1000);
    }
    // 等待所有线程结束(out while loop)
for (int i = 0; i < data.num_of_philos; i++)
        if (pthread_join(data.philos[i].thread, NULL) != 0)
            printf("Error joining thread %d\n", i);
    // 清理资源(out while loop)
    for (int i = 0; i < data.num_of_philos; i++)
        pthread_mutex_destroy(&data.forks[i]);
    pthread_mutex_destroy(&data.write);
    free(data.forks);
    free(data.philos);
    return (0);
}
