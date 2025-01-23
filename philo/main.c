/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:05:06 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/23 20:29:28 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Used to destroy all (unlocked!) mutexes and free all pointers after
	the simulation has stopped.
*/
int	ph_clean_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nb_philos)
		pthread_mutex_destroy(&dinner->forks[i]);
	pthread_mutex_destroy(&dinner->init);
	pthread_mutex_destroy(&dinner->status);
	pthread_mutex_destroy(&dinner->print);
	free(dinner->philos_th);
	free(dinner->philos);
	free(dinner->forks);
	free(dinner);
	return (0);
}

/*
	Joins back all the philos and the monitor to the main thread,
	allowing them to finish before destroying mutexes and freeing pointers.
*/
void	ph_stop_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nb_philos)
		pthread_join(dinner->philos_th[i], 0);
	if (dinner->nb_philos > 1)
		pthread_join(dinner->monitor, 0);
	ph_clean_dinner(dinner);
}

/*
	Starts the simulation by creating a thread for each philosopher,
	if the number of philo is more than 1, creates a monitor also.
*/
int	ph_start_dinner(t_dinner *dinner)
{
	int	i;

	if (dinner->n_meals == 0)
		return (0);
	dinner->philos_th = malloc(sizeof(pthread_t) * dinner->nb_philos);
	if (!dinner->philos_th)
		return (ph_print_err("Error malloc-ing philo_th"));
	dinner->start = ph_gettime() + (dinner->nb_philos * 2);
	i = -1;
	while (++i < dinner->nb_philos)
	{
		if (pthread_create(&dinner->philos_th[i], 0, \
			&ph_routine, (void *)&dinner->philos[i]))
			return (ph_print_err("Error creating philo_th"));
	}
	if (dinner->nb_philos > 1)
	{
		if (pthread_create(&dinner->monitor, 0, &ph_monitor, \
			(void *)dinner))
			return (ph_print_err("Error creating philo_th"));
	}
	ph_stop_dinner(dinner);
	return (0);
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	dinner = NULL;
	if (ac < 5 || ac > 6 || ph_check_args(ac - 1, av))
		return (ph_print_usage());
	dinner = ph_init_simulation(ac, av);
	if (ph_start_dinner(dinner))
		return (1);
	return (0);
}
