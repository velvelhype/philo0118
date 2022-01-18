#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "libft/libft.h"
#include <sys/time.h>

typedef struct s_status
{
	int max_number;
	int number;
	int	time_to_die;
	size_t	*last_meal_times;
	int	eat_time;
	int sleep_time;
	int	eat_limit;
	size_t	*eat_counts;
	int *forks;
	pthread_mutex_t *fork_mutex;
	pthread_mutex_t act_mtx;
	pthread_mutex_t talk_mtx;
} t_status;

int		custom_atoi(const char *str);
void	*philo_life(void *p);
void	error_exit();
size_t	get_time();