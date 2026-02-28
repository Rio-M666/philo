/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrio <mrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:58:23 by mrio              #+#    #+#             */
/*   Updated: 2026/02/28 18:57:40 by mrio             ###   ########.fr       */
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

int	check(int ac, char *av[])
{
	int	i;
	int	j;

	i = 0;
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
	return (0);
}

void	start_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]);
		i++;
	}
	pthread_create(&data->monitor_thread, NULL, monitor, data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
}

int	main(int ac, char *av[])
{
	int		i;
	t_data	data;

	if (check(ac, av))
		return (1);
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
		return (case_one(&data));
	i = 0;
	start_thread(&data);
	ft_exit(&data);
	return (0);
}
