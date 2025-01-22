/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:12:41 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 17:59:11 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Small function used by the philosophers to check whether the simulation
	has stopped, either because one of them is dead or because
	they all had their meals.
*/
int	ph_is_stopped(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner->status);
	if (philo->dinner->completed)
	{
		pthread_mutex_unlock(&philo->dinner->status);
		return (1);
	}
	pthread_mutex_unlock(&philo->dinner->status);
	return (0);
}

/*
	"Kills" a philosopher if he has spent too long without a meal
	and raises the 'completed' flag, putting an end to the simulation.
*/
int	ph_check_starvation(t_dinner *dinner, int i)
{
	if (ph_gettime() - dinner->philos[i].last_meal > dinner->t_die)
	{
		dinner->completed = 1;
		printf("[%llu] ", ph_gettime() - dinner->start);
		printf("%d ", i + 1);
		printf("%s\n", HAS_DIED);
		pthread_mutex_unlock(&dinner->status);
		return (1);
	}
	return (0);
}

/*
	Checks the flag 'all_ate' and, if positive, raises the 'completed' flag,
	prints the end of the simulation and returns 1.
*/
int	ph_check_meals(t_dinner *dinner, int all_ate)
{
	if (dinner->n_meals > 0 && all_ate == 1)
	{
		pthread_mutex_lock(&dinner->status);
		dinner->completed = 1;
		pthread_mutex_unlock(&dinner->status);
		ph_print_complete(dinner);
		return (1);
	}
	return (0);
}

/*
	Checks the current state of every philo to monitor if one has died or
	if everyone has eaten the specified number of meals.
*/
int	ph_check_status(t_dinner *dinner)
{
	int	i;
	int	all_ate;

	all_ate = 1;
	i = -1;
	pthread_mutex_lock(&dinner->status);
	while (++i < dinner->nb_philos)
	{
		if (ph_check_starvation(dinner, i))
			return (1);
		if (dinner->philos[i].meals < dinner->n_meals)
			all_ate = 0;
	}
	pthread_mutex_unlock(&dinner->status);
	return (ph_check_meals(dinner, all_ate));
}

/*
    Checks that all the arguments are positive, valid integers,
    and that av[0] (the number of philos) is within 1-200 range.
*/
int	ph_check_args(int ac, char **av)
{
	int	i;
	int	tmp;

	i = -1;
	av++;
	while (++i < ac)
	{
		if (!ph_is_integer(av[i]))
			return (1);
		tmp = ph_atoll(av[i]);
		if (!i && (tmp < 1 || tmp > 200))
			return (1);
		else if (i == 4 && (tmp < 0 || tmp > INT_MAX))
			return (1);
		else if (i && i < 4 && (tmp < 60 || tmp > INT_MAX))
			return (1);
	}
	return (0);
}
