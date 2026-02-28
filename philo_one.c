/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrio <mrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:45:08 by mrio              #+#    #+#             */
/*   Updated: 2026/02/28 18:55:52 by mrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_one(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	while (!is_dead(philo->data))
		ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

int	case_one(t_data *data)
{
	pthread_create(&data->philo[0].thread, NULL, philo_one, &data->philo[0]);
	pthread_create(&data->monitor_thread, NULL, monitor, data);
	pthread_join(data->philo[0].thread, NULL);
	pthread_join(data->monitor_thread, NULL);
	return (0);
}
