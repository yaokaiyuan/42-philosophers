#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 5 && argc != 6)
    {
        printf("错误：参数数量不正确\n");
        return (1);
    }
    if (init(&data, argc, argv))
        return (1);
    // 创建哲学家线程
    for (int i = 0; i < data.num_of_philos; i++)
    {
        if (pthread_create(&data.philos[i].thread, NULL, philosopher, &data.philos[i]))
        {
            printf("错误：无法创建线程\n");
            return (1);
        }
    }
    // 检查死亡情况
    while (!check_death(&data))
        usleep(1000);
    // 等待所有线程结束
    for (int i = 0; i < data.num_of_philos; i++)
        pthread_join(data.philos[i].thread, NULL);
    // 清理资源
    for (int i = 0; i < data.num_of_philos; i++)
        pthread_mutex_destroy(&data.forks[i]);
    pthread_mutex_destroy(&data.write);
    free(data.forks);
    free(data.philos);
    return (0);
}