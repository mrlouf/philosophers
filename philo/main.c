/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:05:06 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/20 12:32:01 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Used to free all pointers after the simulation has stopped.
*/
void	ph_clean_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	ph_wait(10);
	while (++i < dinner->nb_philos)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
	}
	pthread_mutex_destroy(&dinner->init);
	pthread_mutex_destroy(&dinner->status);
	pthread_mutex_destroy(&dinner->print);
	free(dinner->philos_th);
	free(dinner->philos);
	free(dinner->forks);
	return ;
}

/*
	Starts the simulation and stops if:
	- A philo starves
	- Each philo eats the required number of meals (dinner->n_meals),
	if specified by av[5]
*/
int	ph_start_dinner(t_dinner *dinner)
{
	int	i;

	if (!dinner->n_meals)
	{
		ph_clean_dinner(dinner);
		return (0);
	}
	dinner->philos_th = malloc(sizeof(pthread_t) * dinner->nb_philos);
	if (!dinner->philos_th)
		return (ph_print_err("Error malloc-ing philo_th"));
	i = -1;
	while (++i < dinner->nb_philos)
	{
		if (pthread_create(&dinner->philos_th[i], 0, \
			&ph_routine, (void *)&dinner->philos[i]))
			return (ph_print_err("Error creating philo_th"));
		if (pthread_detach(dinner->philos_th[i]))
			return (ph_print_err("Error detaching philo_th"));
	}
	ph_wait(dinner->t_die / 2);
	if (pthread_create(&dinner->monitor, 0, \
		&ph_monitor, (void *)dinner))
		return (ph_print_err("Error creating philo_th"));
	pthread_join(dinner->monitor, 0);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac >= 5 && ac <= 6 && !ph_check_args(ac - 1, av))
		return (ph_init_simulation(ac, av));
	else
		return (ph_print_usage());
}
