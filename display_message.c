#include "philo.h"

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
			// j = j * -1;
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

void	error_exit()
{
	write(1, "error\n", 7);
	exit(2);
}

size_t	get_time(void)
{
	struct	timeval	times;

	if (gettimeofday(&times, NULL))
		error_exit();
    return ((times.tv_sec * 1000) + (times.tv_usec / 1000));
}

// int main()
// {
// 	printf_time();
// 	int i = 0;
// 	// while(i++ < 100)
// 	// 	usleep(100);
// 	size_t ini = get_time();
// 	while(1)
// 	{
// 		// printf("%lld\n", get_time());
// 		if (get_time() - ini >= 10)
// 			break;
// 	}
// 	printf_time();
// }