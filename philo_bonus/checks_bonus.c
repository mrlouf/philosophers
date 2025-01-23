/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:31:18 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/23 15:31:42 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	Checks if the dinner is completed, returns 1 if it is, 0 otherwise.
*/
int	ph_is_complete(t_philo *philo)
{
	sem_wait(philo->dinner->status);
	if (philo->dinner->completed)
	{
		sem_post(philo->dinner->status);
		return (1);
	}
	sem_post(philo->dinner->status);
	return (0);
}

/*
	Checks if the philo has eaten enough meals, returns 1 if it has, 0 otherwise.
*/
int	ph_is_philofull(t_philo *philo)
{
	sem_wait(philo->counter);
	if (philo->meals >= philo->dinner->n_meals)
	{
		sem_post(philo->counter);
		return (1);
	}
	sem_post(philo->dinner->status);
	return (0);
}

/*
	Monitoring thread that checks if the philo has died or if the dinner is
	complete. If so, it exits the program with different exit status.
*/
void	*ph_monitor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		sem_wait(philo->counter);
		if (ph_gettime() - philo->last_meal > philo->dinner->t_die)
		{
			sem_post(philo->counter);
			ph_print_status(philo->dinner, HAS_DIED, philo->id);
			sem_wait(philo->dinner->status);
			philo->dinner->completed = 1;
			sem_post(philo->dinner->status);
			sem_wait(philo->dinner->print);
			exit (EXIT_FAILURE);
		}
		sem_post(philo->counter);
		usleep(10);
	}
	return (NULL);
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
