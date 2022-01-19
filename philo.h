#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include "libft/libft.h"
# include <sys/time.h>

typedef struct s_status
{
	int				max;
	int				number;
	int				time_to_die;
	int				eat_time;
	int				sleep_time;
	int				*forks;
	size_t			*last_meal_t;
	size_t			eat_limit;
	size_t			*eat_counts;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	act_mtx;
	pthread_mutex_t	talk_mtx;
}	t_status;

int		custom_atoi(const char *str);
void	*philo_life(void *p);
void	error();
size_t	get_time(void);

#endif