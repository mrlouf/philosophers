/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:10:48 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 10:31:16 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ph_init_sems(t_dinner *dinner)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	dinner->forks = sem_open("/forks", O_CREAT, 0644, dinner->nb_philos);
	dinner->print = sem_open("/print", O_CREAT, 0644, 1);
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
	dinner->forks = NULL;
	dinner->philos = NULL;
	return (0);
}

t_dinner	*ph_init_simulation(int ac, char **av)
{
	t_dinner	*dinner;

	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		return (NULL);
	if (ph_init_dinner(ac, av, dinner))
		return (NULL);
	if (ph_init_sems(dinner))
		return (NULL);
	return (dinner);
}
