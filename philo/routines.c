/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:28:02 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 17:08:05 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	This routine waits for all the philos to have eaten all of their meals if
	specified, or until on of them starves.
	TODO
	Do the necessary status checks
	Print death message if anyone dies
*/
void	*ph_monitor(void *data)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)data;
	ph_wait(2000);
	printf("Number of live philos: %d\n", dinner->live_philos);
	return (NULL);
}

/*
	The dining routine for each philosopher: eat, think, sleep, repeat.
	TODO
	- implement the routine:
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
		pthread_mutex_lock(&philo->l_fork);
		printf("#%d has taken a fork 🍴\n", philo->id);
		pthread_mutex_lock(&philo->r_fork);
		printf("#%d has taken a fork 🍴\n", philo->id);
		printf("#%d is eating 🍝\n", philo->id);
		ph_wait(philo->dinner->t_eat);
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
		printf("#%d is sleeping 😴\n", philo->id);
		ph_wait(philo->dinner->t_sleep);
		printf("#%d is thinking 💡\n", philo->id);
	}
	return (NULL);
}
