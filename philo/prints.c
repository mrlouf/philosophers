/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:24:24 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 17:40:43 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_print_status(t_dinner *dinner, char *str, int id)
{
	pthread_mutex_lock(&dinner->print);
	printf("[%lu] ", ph_gettime());
	printf("%d ", id);
	printf("%s\n", str);
	pthread_mutex_unlock(&dinner->print);
}

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
	A debug function that prints all the data pertaining to the dinner and
	returns 1.
*/
int	ph_print_usage(void)
{
	printf("Correct usage: ");
	printf("./philo ");
	printf("nb_of_philosophers (1-200) ");
	printf("time_to_die (60-INT_MAX) ");
	printf("time_to_eat (60-INT_MAX) ");
	printf("time_to_sleep (60-INT_MAX) ");
	printf("[optional: meals_per_each_philosopher (0-INT_MAX)]\n");
	return (1);
}
