#include "philo.h"

void	timer(int time)
{
	size_t ini;

	if (time == 0)
		return ;
	ini = get_time();
	while(1)
	{
		if (get_time() - ini >= time)
			return ;
		usleep(100);
	}
}

void	action(char *message, t_status *stat, int code_number, int time)
{
	pthread_mutex_lock(&stat->talk_mtx);
	printf("%zu ", get_time());
	if (!ft_strncmp("fork", message, ft_strlen(message)))
		printf("%d has taken a fork\n", code_number + 1);
	if (!ft_strncmp("eat", message, ft_strlen(message)))
	{
		printf("%d is eating\n", code_number + 1);
		stat->last_meal_times[code_number] = get_time();
	}
	if (!ft_strncmp("sleep", message, ft_strlen(message)))
	{
		printf("%d is sleeping\n", code_number + 1);
	}
	if (!ft_strncmp("think", message, ft_strlen(message)))
		printf("%d is thinking\n", code_number + 1);
	pthread_mutex_unlock(&stat->talk_mtx);
	timer(time);
}

int fork_number(int fork_number, int max_number)
{
	if (fork_number == max_number)
		fork_number = 0;
	else if (fork_number == -1)
		fork_number = max_number - 1;
	return (fork_number);
}

void take_a_fork(t_status *stat, int code_number)
{
	while (1)
	{
		if (stat->forks[fork_number(code_number, stat->max_number)] &&
			stat->forks[fork_number(code_number + 1, stat->max_number)])
		{
			pthread_mutex_lock(&stat->fork_mutex[fork_number(code_number, stat->max_number)]);
			pthread_mutex_lock(&stat->fork_mutex[fork_number(code_number + 1, stat->max_number)]);
			stat->forks[fork_number(code_number + 1, stat->max_number)] = 0;
			action("fork", stat, code_number, 0);
			stat->forks[fork_number(code_number, stat->max_number)] = 0;
			action("fork", stat, code_number, 0);
			action("eat", stat, code_number, stat->eat_time);
			(stat->eat_counts[code_number])++;
			stat->forks[fork_number(code_number, stat->max_number)] = 1;
			stat->forks[fork_number(code_number + 1, stat->max_number)] = 1;
			pthread_mutex_unlock(&stat->fork_mutex[fork_number(code_number, stat->max_number)]);
			pthread_mutex_unlock(&stat->fork_mutex[fork_number(code_number + 1, stat->max_number)]);
			return;
		}
	}
}

void *philo_life(void *p)
{
	t_status *stat = p;
	stat->number -= 1;
	int code_number = stat->number;
	stat->last_meal_times[code_number] = get_time();
	while (1)
	{
		take_a_fork(stat, code_number);
		action("sleep", stat, code_number, stat->sleep_time);
		usleep(100);
		action("think", stat, code_number, 0);
	}
	return (NULL);
}