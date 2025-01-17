/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:34:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 14:34:20 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Starts the simulation and stops if:
	- A philo starves
	- Each philo eats the required number of meals (dinner->n_meals),
	if specified by av[5]
*/
int	ph_start_dinner(t_dinner *dinner)
{
	int	i;

	dinner->philos_th = malloc(sizeof(pthread_t) * dinner->nb_philos);
	if (!dinner->philos_th)
		return (ph_print_err("Error malloc-ing philo_th"));
	i = -1;
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i].id = i;
		if (pthread_create(&dinner->philos_th[i], 0, \
			&ph_routine, (void *)&dinner->philos[i]))
			return (ph_print_err("Error creating philo_th"));
		if (pthread_detach(dinner->philos_th[i]))
			return (ph_print_err("Error detaching philo_th"));
	}
	if (pthread_create(&dinner->monitor, 0, \
		&ph_monitor, (void *)&dinner->philos[i]))
		return (ph_print_err("Error creating philo_th"));
	pthread_join(dinner->monitor, 0);
	ph_clean_dinner(dinner);
	return (0);
}
