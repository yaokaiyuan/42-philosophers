#include "philo.h"

void eat(t_philo *philo)
{
    t_data *data = philo->data;

    pthread_mutex_lock(&data->forks[philo->left_fork]);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&data->forks[philo->right_fork]);
    print_status(philo, "has taken a fork");
    if (check_death(data))
    {
        pthread_mutex_unlock(&data->forks[philo->left_fork]);
        pthread_mutex_unlock(&data->forks[philo->right_fork]);
        return;
    }
    print_status(philo, "is eating");
    philo->last_eat = get_time();
    usleep(data->time_to_eat * 1000);
    philo->eat_count++;
    pthread_mutex_unlock(&data->forks[philo->left_fork]);
    pthread_mutex_unlock(&data->forks[philo->right_fork]);
}

void sleep_think(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->data->time_to_sleep * 1000);
    print_status(philo, "is thinking");
}

void *philosopher(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *data = philo->data;

    if (data->num_of_philos == 1)
    {
        print_status(philo, "has taken a fork");
        usleep(data->time_to_die * 1000);
        print_status(philo, "died");
        data->dead = 1;
        return (NULL);
    }
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!data->dead && (data->must_eat == -1 || philo->eat_count < data->must_eat))
    {
        if (data->dead)
            break;
        eat(philo);
        sleep_think(philo);
    }
    return (NULL);
}

int check_death(t_data *data)
{
    int i;
    long long current_time;

    i = -1;
    while (++i < data->num_of_philos)
    {
        pthread_mutex_lock(&data->mutex);
        current_time = get_time();
        if (current_time - data->philos[i].last_eat > data->time_to_die)
        {
            print_status(&data->philos[i], "died");
            data->dead = 1;  // 设置死亡标志
            pthread_mutex_unlock(&data->mutex);
            return (1);
        }
        pthread_mutex_unlock(&data->mutex);
    }
    return (0);
}

void print_status(t_philo *philo, char *status)
{
    t_data *data = philo->data;

    pthread_mutex_lock(&data->write);
    if (!data->dead)
        printf("%lld %d %s\n", get_time() - data->start_time, philo->id, status);
    pthread_mutex_unlock(&data->write);
}

long long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}