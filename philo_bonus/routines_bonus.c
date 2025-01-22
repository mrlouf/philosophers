/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by nicolas           #+#    #+#             */
/*   Updated: 2025/01/22 12:08:09 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	Just like the mandatory part, a lone philo needs a special routine
	to avoid hanging on the semaphore, desperately waiting for a fork.
*/
void	ph_lone_philo(t_philo *philo)
{
	sem_wait(philo->dinner->forks);
	ph_print_status(philo->dinner, TAKEN_FORK, philo->id);
	usleep(philo->dinner->t_die * 1000);
	sem_post(philo->dinner->forks);
	ph_print_status(philo->dinner, HAS_DIED, philo->id);
	return ;
}

void	ph_eat(t_philo *philo)
{
	sem_wait(philo->dinner->forks);
	ph_print_status(philo->dinner, TAKEN_FORK, philo->id);
	sem_wait(philo->dinner->forks);
	ph_print_status(philo->dinner, TAKEN_FORK, philo->id);
	ph_print_status(philo->dinner, IS_EATING, philo->id);
	usleep(philo->dinner->t_eat * 1000);
	philo->last_meal = ph_gettime();
	philo->meals++;
	sem_post(philo->dinner->forks);
	sem_post(philo->dinner->forks);
	ph_print_status(philo->dinner, IS_SLEEPING, philo->id);
	usleep(philo->dinner->t_sleep * 1000);
	ph_print_status(philo->dinner, IS_THINKING, philo->id);
}

void	ph_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		ph_eat(philo);
	}
	return ;
}
