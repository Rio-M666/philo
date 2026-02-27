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
		pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philo[i].data = data;
		i++;
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
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
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
int	is_dead(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->dead_mutex);
	flag = data->someone_dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (flag);
}
void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
}
void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	release_forks(philo);
}
void	sleep_philo(t_philo *philo)
{
	ft_usleep(philo->data->time_to_sleep);
}
void	think(t_philo *philo)
{
	(void)philo;
	printf("think\n");
}
void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!is_dead(philo->data))
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
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
		pthread_mutex_lock(&data->dead_mutex);
		data->someone_dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		printf("%ld %d died\n", now - data->start_time, data->philo[i].id);
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
		ft_usleep(1000);
	}
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
	data.start_time = get_time();
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
	return (0);
}
