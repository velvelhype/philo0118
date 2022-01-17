#include "philo.h"

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