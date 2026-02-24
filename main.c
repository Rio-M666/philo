#include "philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meal_count = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philo[i].data = data;
	}
}
int	init(int ac, char *av[], t_data *data)
{
	int	i;

	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	if (data->nb_philo <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->start_time = 0;
	data->someone_dead = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	return (0);
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
	init_philos(&data);
	return (0);
}
