/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:29:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/23 10:22:33 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	Prints the final message when the dinner is complete, ie. when all philos
	have eaten the specified number of meals.
*/
void	ph_print_complete(t_dinner *dinner)
{
	sem_wait(dinner->print);
	printf("\n");
	printf("Dinner completed!\n");
	printf("\n");
	printf("\"To live is to suffer,\n");
	printf("to survive is to find meaning in the suffering.\"\n");
	printf("\n");
	printf("Friederich Nietzsche\n");
	sem_post(dinner->print);
	return ;
}

/*
	Print function used to display all the status update with the timestamp.
	The print mutex prevents any message coincidence.
*/
void	ph_print_status(t_dinner *dinner, char *str, int id)
{
	sem_wait(dinner->status);
	if (dinner->completed)
	{
		sem_post(dinner->status);
		return ;
	}
	sem_post(dinner->status);
	sem_wait(dinner->print);
	printf("[%llu] ", ph_gettime() - dinner->start);
	printf("%d ", id);
	printf("%s\n", str);
	sem_post(dinner->print);
	return ;
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
	printf("Dining with %d philos, dying in %lu ms, \
eating for %lu, sleeping for %lu", \
		dinner->nb_philos, dinner->t_die, \
		dinner->t_eat, dinner->t_sleep);
	if (dinner->n_meals > 0)
		printf(", eating %d meals", dinner->n_meals);
	printf("\n");
	return ;
}

/*
	An error message displayed in case of incorrect input.
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
