/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:12:13 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/09/09 22:46:56 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    int             eat_count;
    long long       last_eat;
    struct s_data   *data;
    pthread_t       thread;
} t_philo;

typedef struct s_data
{
    int             num_of_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    int             dead;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t write;
    pthread_mutex_t mutex;
    t_philo         *philos;
} t_data;

int     init(t_data *data, int argc, char **argv);
void    *philosopher(void *arg);
void    eat(t_philo *philo);
void    sleep_think(t_philo *philo);
int     check_death(t_data *data);
long long get_time(void);
void    print_status(t_philo *philo, char *status);
void    print_died(t_philo *philo);

#endif
