/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrio <mrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:58:09 by mrio              #+#    #+#             */
/*   Updated: 2026/02/28 18:15:48 by mrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat(t_philo *philo)
{
	if (is_dead(philo->data))
		return ;
	take_forks(philo);
	if (is_dead(philo->data))
	{
		release_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	release_forks(philo);
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_dead(philo->data))
	{
		eat(philo);
		sleep_philo(philo);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
