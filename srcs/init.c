#include "philo.h"

static int init_mutexes(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
    if (!data->forks)
        return (1);
    for (i = 0; i < data->num_of_philos; i++)
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (1);
    if (pthread_mutex_init(&data->write, NULL))
        return (1);
    return (0);
}

static int init_philos(t_data *data)
{
    int i;

    data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
    if (!data->philos)
        return (1);
    for (i = 0; i < data->num_of_philos; i++)
    {
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = i;
        data->philos[i].right_fork = (i + 1) % data->num_of_philos;
        data->philos[i].eat_count = 0;
        data->philos[i].last_eat = get_time();
        data->philos[i].data = data;
    }
    return (0);
}

int init(t_data *data, int argc, char **argv)
{
    data->num_of_philos = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    data->must_eat = (argc == 6) ? atoi(argv[5]) : -1;
    data->dead = 0;
    data->start_time = get_time();
    if (init_mutexes(data) || init_philos(data))
        return (1);
    return (0);
}