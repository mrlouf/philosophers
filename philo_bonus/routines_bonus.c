/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by nicolas           #+#    #+#             */
/*   Updated: 2025/01/22 11:48:43 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
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

void	*ph_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		eat(philo);
	}
	return (NULL);
}
