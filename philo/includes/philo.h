/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:12:27 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/12/23 15:45:12 by ykai-yua         ###   ########.fr       */
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
# include <stdbool.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				fork[2];
	int				eat_count;
	pthread_mutex_t	meal_time_lock;
	time_t			last_eat;
	struct s_data	*data;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	pthread_t		monitor;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	time_t			start_time;
	bool			stop_time;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	t_philo			**philos;
}	t_data;
typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

void	*free_data(t_data *data);
void	destroy_mutexes(t_data *data);
int		msg(char *str, char *detail, int exit_no);
int		error_failure(char *str, char *details, t_data *data);
void	*error_null(char *str, char *details, t_data *data);

t_data	*init_table(int ac, char **av, int i);

bool	has_simulation_stopped(t_data *data);
void	*monitor(void *input);

int		integer_atoi(char *str);
bool	is_valid_input(int ac, char **av);

void	*philosopher(void *data);

time_t	get_time_in_ms(void);
void	philo_sleep(t_data *data, time_t sleep_time);
void	sim_start_delay(time_t start_time);

int		main(int ac, char **av);

void	write_status(t_philo *philo, bool reaper_report, t_status status);

#endif
