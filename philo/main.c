/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:05:06 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 17:13:08 by nponchon         ###   ########.fr       */
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

	ph_print_dinner(dinner);
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
		&ph_monitor, (void *)dinner))
		return (ph_print_err("Error creating philo_th"));
	pthread_join(dinner->monitor, 0);
	ph_clean_dinner(dinner);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac >= 5 && ac <= 6 && !ph_check_args(ac - 1, av))
		return (ph_init_simulation(ac, av));
	else
		return (ph_print_usage());
}
