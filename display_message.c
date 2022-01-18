#include "philo.h"

void	*malloc_or_exit(size_t size)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
		error_exit();
	return (p);
}

int	custom_atoi(const char *str)
{
	unsigned long	i;
	int				j;
	unsigned long	sum;

	sum = 0;
	i = 0;
	j = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			error_exit();
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		sum = (sum * 10) + str[i] - '0';
		i++;
	}
	if (ft_isalpha(str[i]))
		error_exit();
	return ((int)j * sum);
}

void	error_exit(void)
{
	write(1, "error\n", 7);
	exit(2);
}

size_t	get_time(void)
{
	struct timeval	times;

	if (gettimeofday(&times, NULL))
		error_exit();
	return ((times.tv_sec * 1000) + (times.tv_usec / 1000));
}
