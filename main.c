#include "philo.h"

void	*malloc_or_exit(size_t size)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
		error_exit();
	return (p);
}

void	init_status(t_status *stat, int argc, char **argv)
{
	stat->max_number = custom_atoi(argv[1]);
	stat->number = custom_atoi(argv[1]);
	stat->time_to_die = custom_atoi(argv[2]);
	stat->last_meal_times = (size_t *)malloc_or_exit(sizeof(size_t) * stat->max_number);
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
	stat->eat_counts = (size_t *)malloc_or_exit(sizeof(size_t) * stat->max_number);
	stat->forks = (int *)malloc_or_exit(sizeof(int) * stat->max_number);
	stat->fork_mutex = (pthread_mutex_t *)malloc_or_exit
	(sizeof(pthread_mutex_t) * stat->max_number);
	for (int i = 0; i < stat->max_number; i++)
		stat->forks[i] = 1;
	pthread_mutex_init(&stat->talk_mtx, NULL);
	for (int i = 0; i < stat->max_number; i++)
		pthread_mutex_init(&stat->fork_mutex[i], NULL);
}

void	are_philos_full(t_status *stat)
{
	if (stat->eat_limit == 0)
		return ;
	for (int i = 0; i < stat->max_number; i++)
	{
		if (stat->eat_counts[i] < stat->eat_limit)
			return ;
	}
	exit(1);
}

void	are_philos_starved(t_status *stat)
{
	size_t now;

	now = get_time();
	for (int i = 0; i < stat->max_number; i++)
	{
		if (stat->last_meal_times[i] + stat->time_to_die <= now)
		{
			printf("%zu ", get_time());
			printf("%d died\n", i + 1);
			exit(1);
		}
	}
}

int main(int argc, char **argv)
{
	t_status stat;
	if (argc != 5 && argc != 6)
		error_exit();
	init_status(&stat, argc, argv);
	pthread_t *philos;
	philos = (pthread_t *)malloc_or_exit(sizeof(pthread_t) * stat.max_number);
	for (int i = 0; i < stat.max_number; i++)
	{
		if (pthread_create(&philos[i], NULL, &philo_life, &stat))
			error_exit();
		pthread_detach(philos[i]);
		usleep(500);
	}
	while (1)
	{
		are_philos_starved(&stat);
		are_philos_full(&stat);
	}
}