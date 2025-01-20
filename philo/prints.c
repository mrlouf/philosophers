/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:24:24 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/20 17:46:59 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_print_death(t_dinner *dinner, int i)
{
	pthread_mutex_lock(&dinner->status);
	dinner->dead_philo = 1;
	pthread_mutex_unlock(&dinner->status);
	pthread_mutex_lock(&dinner->print);
	printf("[%llu] ", ph_gettime() - dinner->start);
	printf("Simulation ended because %d has died\n", dinner->philos[i].id);
	pthread_mutex_unlock(&dinner->print);
	return (1);
}

/*
	Prints the final message when the dinner is complete, ie. when all philos
	have eaten the specified number of meals.
*/
void	ph_print_complete(t_dinner *dinner)
{
	pthread_mutex_lock(&dinner->print);
	printf("\n");
	printf("Dinner completed!\n");
	printf("\n");
	printf("\"To live is to suffer,\n");
	printf("to survive is to find meaning in the suffering.\"\n");
	printf("\n");
	printf("Friederich Nietzsche\n");
	pthread_mutex_unlock(&dinner->print);
}

/*
	Print function used to display all the status update with the timestamp.
	The print mutex prevents any message coincidence.
*/
void	ph_print_status(t_dinner *dinner, char *str, int id)
{
	pthread_mutex_lock(&dinner->status);
	if (dinner->dead_philo == 0)
	{
		pthread_mutex_unlock(&dinner->status);
		pthread_mutex_lock(&dinner->print);
		printf("[%llu] ", ph_gettime() - dinner->start);
		printf("%d ", id);
		printf("%s\n", str);
		pthread_mutex_unlock(&dinner->print);
		return ;
	}
	pthread_mutex_unlock(&dinner->status);
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
