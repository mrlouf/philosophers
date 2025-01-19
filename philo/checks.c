/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:12:41 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/19 20:33:25 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Checks the current state of every philo to monitor if one has died or
	if everyone has eaten the specified number of meals.
*/
int	ph_check_status(t_dinner *dinner)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&dinner->status);
	while (++i < dinner->nb_philos)
	{
		if (dinner->philos[i].is_alive == 0)
		{
			dinner->dead_philo = dinner->philos[i].id;
			pthread_mutex_unlock(&dinner->status);
			return (1);
		}
		else if (dinner->philos[i].meals < dinner->n_meals)
			break ;
		else if (i + 1 == dinner->nb_philos)
		{
			pthread_mutex_unlock(&dinner->status);
			ph_print_complete(dinner);
			return (1);
		}
	}
	pthread_mutex_unlock(&dinner->status);
	return (0);
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
