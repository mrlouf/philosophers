/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:34:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 12:15:48 by nponchon         ###   ########.fr       */
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
	i = -1;
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i].id = i;
		if (pthread_create(&dinner->philos_th[i], 0, \
			&ph_routine, (void *)&dinner->philos[i]))
			return (ph_print_err("Error creating philo_th"));
		if (pthread_detach(dinner->philos_th[i]))
			return (ph_print_err("Error detaching philo"));
	}
	if (pthread_create(&dinner->monitor, 0, \
		&ph_monitor, (void *)&dinner->philos[i]))
		return (ph_print_err("Error creating philo_th"));
	pthread_join(dinner->monitor, 0);
	free(dinner->philos);
	return (0);
}

void	*ph_monitor(void *data)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)data;
	while (!dinner->dead_philo)
		;
	printf("One philosopher died\n");
	return (NULL);
}

/*
	The dining routine for each philosopher: eat, think, sleep, repeat.
	TODO
	- implement the routine
*/
void	*ph_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("Philosopher (thread) #%i created\n", philo->id);
	return (NULL);
}

/*
	Initialises each t_philo structure with the necessary information
	for each thread to complete the simulation.
*/
int	ph_init_philos(t_dinner *dinner)
{
	int	i;

	dinner->philos = malloc(sizeof(t_philo) * dinner->nb_philos);
	if (!dinner->philos)
		return (ph_print_err("Malloc failed"));
	i = -1;
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i].id = i;
		dinner->philos[i].dinner = dinner;
	}
	return (0);
}

/*
	Initialises the t_dinner structure with the necessary information
	to launch the simulation.
*/
int	ph_init_dinner(int ac, char **av)
{
	t_dinner	dinner;

	memset(&dinner, 0, sizeof(t_dinner));
	dinner.nb_philos = ph_atoll(av[1]);
	dinner.philos = NULL;
	dinner.t_die = ph_atoll(av[2]);
	dinner.t_eat = ph_atoll(av[3]);
	dinner.t_sleep = ph_atoll(av[4]);
	dinner.dead_philo = 0;
	if (ac == 6)
		dinner.n_meals = ph_atoll(av[5]);
	else
		dinner.n_meals = INT_MAX;
	if (ph_init_philos(&dinner) || ph_start_dinner(&dinner))
		return (1);
	return (0);
}
