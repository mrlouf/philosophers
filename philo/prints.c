/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:24:24 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 15:26:23 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Prints an error message and returns 1.
	Used in case malloc fails, incorrect argument, etc.
*/
int	ph_print_err(char *str)
{
	if (str)
		printf("%s\n", str);
	return (1);
}

/*
	A debug function that prints all the data pertaining to the dinner.
*/
void	ph_print_dinner(t_dinner *dinner)
{
	printf("Dining with %d philos, dying in %d ms, \
eating for %d, sleeping for %d", \
		dinner->nb_philos, dinner->t_die, \
		dinner->t_eat, dinner->t_sleep);
	if (dinner->n_meals > 0)
		printf(", eating %d meals", dinner->n_meals);
	printf("\n");
}

/*
	A debug function that prints all the data pertaining to the dinner.
*/
void	ph_print_usage(void)
{
	printf("Correct usage: ");
	printf("./philo ");
	printf("nb_of_philosophers (1-200) ");
	printf("time_to_die (60-INT_MAX) ");
	printf("time_to_eat (60-INT_MAX) ");
	printf("time_to_sleep (60-INT_MAX) ");
	printf("[optional: meals_per_each_philosopher (0-INT_MAX)]\n");
	return ;
}

/*
	Debug function to print the time of the day in seconds and milliseconds.
*/
void	ph_print_tod(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("seconds : %lu\nmicro seconds : %lu\n", \
	current_time.tv_sec, current_time.tv_usec);
	printf("Current time: %lu\n", \
		(current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
