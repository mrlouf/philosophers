/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:39:20 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/20 09:53:22 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Custom usleep function to be more precise than the original by making up
	for delay, tick rate, OS scheduler etc.
*/
void	ph_usleep(long usec)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;
	long			rem;

	elapsed = 0;
	rem = 0;
	gettimeofday(&start, NULL);
	while (elapsed < usec)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) \
		* 1000000L + (current.tv_usec - start.tv_usec);
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}

/*
	Gets the time of the day in seconds and milliseconds.
*/
long long	ph_gettime(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

/*
	Waiting function that takes a long int for milliseconds and converts it
	to microseconds to call usleep.
*/
int	ph_wait(long int ms)
{
	long int	us;

	us = ms * 1000;
	ph_usleep(us);
	return (0);
}

/*
	Checks if a string is a valid integer, ie. if it only contains numbers.
*/
int	ph_is_integer(const char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

long long	ph_atoll(const char *str)
{
	long long	nbr;
	int			sign;

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
