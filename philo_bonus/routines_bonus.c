/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:00:00 by nicolas           #+#    #+#             */
/*   Updated: 2025/01/23 15:23:36 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	Just like the mandatory part, a lone philo needs a special routine
	to avoid hanging on the semaphore, desperately waiting for a fork.
*/
void	ph_lone_philo(t_philo *philo)
{
	ph_delay(philo->dinner->start);
	sem_wait(philo->dinner->forks);
	ph_print_status(philo->dinner, TAKEN_FORK, philo->id);
	ph_sleep(philo->dinner->t_die);
	sem_post(philo->dinner->forks);
	ph_print_status(philo->dinner, HAS_DIED, philo->id);
	ph_clean_dinner(philo->dinner);
	exit(EXIT_SUCCESS);
}

static void	ph_eat_sleep_think(t_philo *philo)
{
	sem_wait(philo->dinner->forks);
	ph_print_status(philo->dinner, TAKEN_FORK, philo->id);
	sem_wait(philo->dinner->forks);
	ph_print_status(philo->dinner, TAKEN_FORK, philo->id);
	ph_print_status(philo->dinner, IS_EATING, philo->id);
	sem_wait(philo->counter);
	philo->last_meal = ph_gettime();
	philo->meals++;
	if (philo->dinner->n_meals != -1
		&& philo->meals >= philo->dinner->n_meals)
	{
		sem_post(philo->counter);
		sem_post(philo->dinner->forks);
		sem_post(philo->dinner->forks);
		exit(0);
	}
	sem_post(philo->counter);
	ph_sleep(philo->dinner->t_eat);
	sem_post(philo->dinner->forks);
	sem_post(philo->dinner->forks);
	ph_print_status(philo->dinner, IS_SLEEPING, philo->id);
	ph_sleep(philo->dinner->t_sleep);
	ph_print_status(philo->dinner, IS_THINKING, philo->id);
}

void	ph_routine(t_philo *philo)
{
	philo->last_meal = philo->dinner->start;
	ph_delay(philo->dinner->start);
	pthread_create(&philo->monitor, NULL, ph_monitor, philo);
	pthread_detach(philo->monitor);
	if (philo->id % 2 == 0)
	{
		ph_print_status(philo->dinner, IS_THINKING, philo->id);
		ph_sleep(philo->dinner->t_sleep);
	}
	while (1)
		ph_eat_sleep_think(philo);
}
