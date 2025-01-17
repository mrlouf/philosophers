/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:28:02 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 18:56:33 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	This routine waits for all the philos to have eaten all of their meals if
	specified, or until on of them starves.
	TODO
	- do the necessary status checks
	- print death message if anyone dies
*/
void	*ph_monitor(void *data)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)data;
	ph_wait(60);
	while (dinner->live_philos < dinner->nb_philos)
		ph_wait(100);
	while (!ph_check_status(dinner))
		ph_wait(dinner->t_die / 2);
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
	ph_print_status(philo->dinner, "has taken a fork 🍴", philo->id);
	pthread_mutex_lock(&philo->r_fork);
	ph_print_status(philo->dinner, "has taken a fork 🍴", philo->id);
	ph_print_status(philo->dinner, "is eating 🍝", philo->id);
	philo->last_meal = ph_gettime();
	pthread_mutex_lock(&philo->dinner->status);
	philo->meals++;
	pthread_mutex_unlock(&philo->dinner->status);
	ph_wait(philo->dinner->t_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

/*
	The dining routine for each philosopher: eat, think, sleep, repeat.
	TODO
	- implement the routine, including status checks and updates
*/
void	*ph_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->dinner->init);
	philo->dinner->live_philos++;
	pthread_mutex_unlock(&philo->dinner->init);
	while (42)
	{
		ph_eating(philo);
		ph_print_status(philo->dinner, "is sleeping 😴", philo->id);
		ph_wait(philo->dinner->t_sleep);
		ph_print_status(philo->dinner, "is thinking 💡", philo->id);
	}
	return (NULL);
}
