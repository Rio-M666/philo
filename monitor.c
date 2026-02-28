/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrio <mrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:10:00 by mrio              #+#    #+#             */
/*   Updated: 2026/02/28 16:16:41 by mrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_data *data, int id)
{
	long	now;

	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->dead_mutex);
	data->someone_dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
	now = get_time();
	printf("%ld %d died\n", now - data->start_time, id);
	pthread_mutex_unlock(&data->print_mutex);
}

int	enough_eat(t_data *data)
{
	int	i;

	i = 0;
	if (data->must_eat == -1)
		return (0);
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philo[i].meal_mutex);
		if (data->philo[i].meal_count < data->must_eat)
		{
			pthread_mutex_unlock(&data->philo[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].meal_mutex);
		i++;
	}
	return (1);
}

int	check_dead(t_data *data, int i)
{
	long	now;
	long	last_meal;

	pthread_mutex_lock(&data->philo[i].meal_mutex);
	last_meal = data->philo[i].last_meal;
	pthread_mutex_unlock(&data->philo[i].meal_mutex);
	now = get_time();
	if (now - last_meal > data->time_to_die)
	{
		set_dead(data, data->philo[i].id);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_dead(data, i))
				return (NULL);
			i++;
		}
		if (enough_eat(data))
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->someone_dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return (NULL);
		}
		usleep(1000);
	}
}
