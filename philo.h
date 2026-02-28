/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrio <mrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:17:25 by mrio              #+#    #+#             */
/*   Updated: 2026/02/28 18:17:31 by mrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					nb_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					must_eat;

	long				start_time;
	int					someone_dead;

	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_t			monitor_thread;

	t_philo				*philo;
}						t_data;

typedef struct s_philo
{
	int					id;
	long				last_meal;
	int					meal_count;

	pthread_t			thread;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;

	t_data				*data;
}						t_philo;

int						parse_args(int ac, char **av, t_data *data);
long					get_time(void);
int						ft_atoi(const char *str);
void					ft_usleep(long long time);
void					*routine(void *philo_pointer);
void					print_action(t_philo *philo, char *str);
int						is_dead(t_data *data);
void					*monitor(void *arg);
int						is_digit(char c);
int						init(int ac, char *av[], t_data *data);
void					init_philos(t_data *data);
#endif
