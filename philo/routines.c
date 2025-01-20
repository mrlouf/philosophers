/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:28:02 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/20 12:05:22 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Special routine for the case where only a lonely philo sits at the table.
	With only one fork, he takes the first one, waits for the specified time to
	starve, and starves. 
*/
int	ph_lone_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	ph_print_status(philo->dinner, TAKEN_FORK, philo->id);
	pthread_mutex_lock(&philo->dinner->status);
	ph_wait(philo->dinner->t_die);
	philo->is_alive = 0;
	ph_print_status(philo->dinner, HAS_DIED, philo->id);
	pthread_mutex_unlock(&philo->dinner->status);
	pthread_mutex_unlock(&philo->l_fork);
	return (0);
}

/*
	This routine waits for all the philos to have eaten all of their meals if
	specified, or until one of them starves.
*/
void	*ph_monitor(void *data)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)data;
	while (!ph_check_status(dinner))
		ph_wait(dinner->t_die / dinner->nb_philos);
	if (dinner->dead_philo)
		printf("Simulation stopped because %i starved\n", dinner->dead_philo);
	ph_clean_dinner(dinner);
	return (NULL);
}

/*
	The processus of eating for every philosopher, locking the forks,
	printing message, updating variables, waiting the t_eat, unlocking forks.
*/
void	ph_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	ph_print_status(philo->dinner, TAKEN_FORK, philo->id);
	pthread_mutex_lock(&philo->r_fork);
	ph_print_status(philo->dinner, TAKEN_FORK, philo->id);
	ph_print_status(philo->dinner, IS_EATING, philo->id);
	philo->last_meal = ph_gettime();
	pthread_mutex_lock(&philo->dinner->status);
	philo->meals++;
	pthread_mutex_unlock(&philo->dinner->status);
	ph_wait(philo->dinner->t_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	ph_print_status(philo->dinner, IS_SLEEPING, philo->id);
	ph_wait(philo->dinner->t_sleep);
	ph_print_status(philo->dinner, IS_THINKING, philo->id);
}

/*
	The dining routine for each philosopher: eat, think, sleep, repeat.
*/
void	*ph_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->dinner->nb_philos == 1)
	{
		ph_lone_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		ph_print_status(philo->dinner, IS_SLEEPING, philo->id);
		ph_wait(philo->dinner->t_sleep);
		ph_print_status(philo->dinner, IS_THINKING, philo->id);
	}
	while ((ph_gettime() - philo->last_meal \
		< philo->dinner->t_die))
		ph_eating(philo);
	ph_print_status(philo->dinner, HAS_DIED, philo->id);
	pthread_mutex_lock(&philo->dinner->status);
	philo->dinner->dead_philo = philo->id;
	pthread_mutex_unlock(&philo->dinner->status);
	return (NULL);
}
