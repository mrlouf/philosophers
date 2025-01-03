#include "philo.h"

/*
	A debug function that prints all the data pertaining to the dinner.
*/
void	ph_print_dinner(t_dinner *dinner)
{
	printf("Dining with %d philos, dying in %d ms, eating for %d, sleeping for %d", \
		dinner->guests, dinner->time_to_die, dinner->time_to_eat, dinner->time_to_sleep);
	if (dinner->number_of_meals > 0)
		printf(", eating %d meals", dinner->number_of_meals);
	printf("\n");
}

/*
	Checks if a string is a valid integer, ie. if it only contains numbers.
*/
int	ft_is_integer(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] != 0)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (nbr * sign);
}
