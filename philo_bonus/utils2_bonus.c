/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:58:33 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/23 12:59:28 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	Gets the time of the day in seconds and milliseconds.
*/
time_t	ph_gettime(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ph_sleep(time_t time)
{
	time_t	start;

	start = ph_gettime() + time;
	while (ph_gettime() < start)
		usleep(100);
}

/*
	Delays the program until the specified time so that all philos and monitors
	start at the same time.
*/
void	ph_delay(long long start)
{
	while (ph_gettime() < start)
		continue ;
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
