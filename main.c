/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrio <mrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:58:23 by mrio              #+#    #+#             */
/*   Updated: 2026/02/28 17:59:38 by mrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->dead_mutex);
	flag = data->someone_dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (flag);
}

void	print_action(t_philo *philo, char *str)
{
	long	now;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->someone_dead)
	{
		now = get_time();
		printf("%ld %d %s\n", now - philo->data->start_time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

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
void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	free(data->forks);
	free(data->philo);
}

int	main(int ac, char *av[])
{
	int		i;
	int		j;
	t_data	data;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (init(ac, av, &data))
		return (1);
	if (data.must_eat == 0)
	{
		free(data.forks);
		free(data.philo);
		return (0);
	}
	data.start_time = get_time();
	init_philos(&data);
	if (data.nb_philo == 1)
	{
		pthread_create(&data.philo[0].thread, NULL, philo_one, &data.philo[0]);
		pthread_create(&data.monitor_thread, NULL, monitor, &data);
		pthread_join(data.philo[0].thread, NULL);
		pthread_join(data.monitor_thread, NULL);
		return (0);
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_create(&data.philo[i].thread, NULL, routine, &data.philo[i]);
		i++;
	}
	pthread_create(&data.monitor_thread, NULL, monitor, &data);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	pthread_join(data.monitor_thread, NULL);
	ft_exit(&data);
	return (0);
}
