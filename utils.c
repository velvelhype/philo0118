#include "philo.h"

void	error()
{
	write(1, "error\n", 7);	
}

int	custom_atoi(const char *str)
{
	unsigned long	i;
	unsigned long	sum;

	sum = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		sum = (sum * 10) + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (sum);
}

size_t	get_time(void)
{
	struct timeval	times;

	gettimeofday(&times, NULL);
	return ((times.tv_sec * 1000) + (times.tv_usec / 1000));
}
