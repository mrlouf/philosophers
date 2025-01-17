/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:36:17 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 13:52:15 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_init_forks(t_dinner *dinner)
{
	int	i;

	i = -1;
	dinner->forks = malloc(sizeof(pthread_mutex_t) * dinner->nb_philos);
	if (!dinner->forks)
		return (1);
	while (++i < dinner->nb_philos)
	{
		if (pthread_mutex_init(&dinner->forks[i], NULL))
			return (ph_print_err("Error creating forks-mutex"));
	}
	return (0);
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
		dinner->philos[i].r_fork = dinner->forks[i];
		if (i != dinner->nb_philos - 1)
			dinner->philos[i].l_fork = dinner->forks[i + 1];
		else
			dinner->philos[i - 1].l_fork = dinner->forks[0];
	}
	return (0);
}

/*
	Initialises the t_dinner structure with the necessary information
	to launch the simulation.
*/
void	ph_init_dinner(int ac, char **av, t_dinner *dinner)
{
	dinner->nb_philos = ph_atoll(av[1]);
	dinner->t_die = ph_atoll(av[2]);
	dinner->t_eat = ph_atoll(av[3]);
	dinner->t_sleep = ph_atoll(av[4]);
	if (ac == 6)
		dinner->n_meals = ph_atoll(av[5]);
	else
		dinner->n_meals = INT_MAX;
	dinner->dead_philo = 0;
	dinner->start = 0;
	dinner->monitor = 0;
	dinner->philos_th = NULL;
	dinner->philos = NULL;
}

/*
	Starts the simulation, initialises the structures and starts
	the dinner.
	Handles error in case a function fails at any stage.
*/
int	ph_init_simulation(int ac, char **av)
{
	t_dinner	dinner;

	memset(&dinner, 0, sizeof(t_dinner));
	ph_init_dinner(ac, av, &dinner);
	if (ph_init_forks(&dinner))
		return (1);
	if (ph_init_philos(&dinner))
		return (1);
	if (ph_start_dinner(&dinner))
		return (1);
	return (0);
}
