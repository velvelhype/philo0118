#include "philo.h"

void	init_count(t_status *stat, int argc, char **argv)
{
	stat->max = custom_atoi(argv[1]);
	stat->number = custom_atoi(argv[1]);
	stat->time_to_die = custom_atoi(argv[2]);
	stat->last_meal_t = (size_t *)malloc_or_exit(sizeof(size_t) * stat->max);
	stat->eat_time = custom_atoi(argv[3]);
	stat->sleep_time = custom_atoi(argv[4]);
	if (argc == 6)
	{
		stat->eat_limit = custom_atoi(argv[5]);
		if (stat->eat_limit <= 0)
			error_exit();
	}
	else
		stat->eat_limit = 0;
}

void	init_status(t_status *stat, int argc, char **argv)
{
	size_t	norm_esc;
	int		i;

	init_count(stat, argc, argv);
	norm_esc = sizeof(size_t) * stat->max;
	stat->eat_counts = (size_t *)malloc_or_exit(norm_esc);
	stat->forks = (int *)malloc_or_exit(sizeof(int) * stat->max);
	norm_esc = sizeof(pthread_mutex_t) * stat->max;
	stat->fork_mutex = (pthread_mutex_t *)malloc_or_exit(norm_esc);
	i = 0;
	while (i < stat->max)
	{
		stat->forks[i] = 1;
		pthread_mutex_init(&stat->fork_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&stat->talk_mtx, NULL);
}

void	are_philos_full(t_status *stat)
{
	int	i;

	if (stat->eat_limit == 0)
		return ;
	i = 0;
	while (i < stat->max)
	{
		if (stat->eat_counts[i] < stat->eat_limit)
			return ;
		i++;
	}
	exit(1);
}

void	are_philos_starved(t_status *stat)
{
	size_t	now;
	int		i;

	i = 0;
	now = get_time();
	while (i < stat->max)
	{
		if (stat->last_meal_t[i] + stat->time_to_die <= now)
		{
			printf("%zu ", get_time());
			printf("%d died\n", i + 1);
			exit(1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_status	stat;
	pthread_t	*philos;
	int			i;

	if (argc != 5 && argc != 6)
		error_exit();
	init_status(&stat, argc, argv);
	philos = (pthread_t *)malloc_or_exit(sizeof(pthread_t) * stat.max);
	i = 0;
	while (i < stat.max)
	{
		if (pthread_create(&philos[i], NULL, &philo_life, &stat))
			error_exit();
		pthread_detach(philos[i]);
		usleep(500);
		i++;
	}
	while (1)
	{
		are_philos_starved(&stat);
		are_philos_full(&stat);
	}
}
