/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:36:17 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 16:50:56 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_delay(long long start)
{
	while (ph_gettime() < start)
		continue ;
}

/*
	Initialises all the forks (mutexes) to be put at the table,
	that is as many as there are philosophers.
*/
int	ph_init_forks(t_dinner *dinner)
{
	int	i;

	dinner->forks = malloc(sizeof(pthread_mutex_t) * dinner->nb_philos);
	if (!dinner->forks)
		return (1);
	i = -1;
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
	Forks are assigned so that the last philo shares its left fork
	as the right fork from the first philo to close the table.
*/
int	ph_init_philos(t_dinner *dinner)
{
	int	i;

	dinner->philos = malloc(sizeof(t_philo) * dinner->nb_philos);
	if (!dinner->philos)
		return (ph_print_err("Error malloc-ing philos"));
	i = -1;
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i].id = i + 1;
		dinner->philos[i].is_alive = 1;
		dinner->philos[i].last_meal = ph_gettime();
		dinner->philos[i].meals = 0;
		dinner->philos[i].l_fork = &dinner->forks[i];
		if (i != dinner->nb_philos - 1)
			dinner->philos[i].r_fork = &dinner->forks[i + 1];
		else
			dinner->philos[i].r_fork = &dinner->forks[0];
		dinner->philos[i].dinner = dinner;
	}
	return (0);
}

/*
	Initialises the t_dinner structure with the user input and sets
	the rest to NULL, initialises the dinner mutexes.
*/
int	ph_init_dinner(int ac, char **av, t_dinner *dinner)
{
	dinner->nb_philos = ph_atoll(av[1]);
	dinner->t_die = ph_atoll(av[2]);
	dinner->t_eat = ph_atoll(av[3]);
	dinner->t_sleep = ph_atoll(av[4]);
	dinner->n_meals = -1;
	if (ac == 6)
		dinner->n_meals = ph_atoll(av[5]);
	dinner->live_philos = 0;
	dinner->completed = 0;
	dinner->start = ph_gettime();
	dinner->monitor = 0;
	dinner->philos_th = NULL;
	dinner->forks = NULL;
	dinner->philos = NULL;
	if (pthread_mutex_init(&dinner->init, NULL))
		return (ph_print_err("Error creating init-mutex"));
	if (pthread_mutex_init(&dinner->status, NULL))
		return (ph_print_err("Error creating status-mutex"));
	if (pthread_mutex_init(&dinner->print, NULL))
		return (ph_print_err("Error creating print-mutex"));
	return (0);
}

/*
	Starts the simulation, initialises the structures and starts
	the dinner.
	Handles error in case a function fails at any stage.
*/
t_dinner	*ph_init_simulation(int ac, char **av)
{
	t_dinner	*dinner;

	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		return (NULL);
	if (ph_init_dinner(ac, av, dinner))
		return (NULL);
	if (ph_init_forks(dinner))
		return (NULL);
	if (ph_init_philos(dinner))
		return (NULL);
	return (dinner);
}
