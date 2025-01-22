/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:10:48 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 11:07:13 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ph_init_philos(t_dinner *dinner)
{
	int	i;

	dinner->philos = malloc(sizeof(t_philo) * dinner->nb_philos);
	if (!dinner->philos)
		return (ph_print_err("Error creating forks-mutex"));
	i = -1;
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i].id = i + 1;
		dinner->philos[i].is_alive = 1;
		dinner->philos[i].meals = 0;
		dinner->philos[i].pid = 0;
		dinner->philos[i].dinner = dinner;
	}
	return (0);
}

int	ph_init_sems(t_dinner *dinner)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	dinner->forks = sem_open("/forks", O_CREAT, 0644, dinner->nb_philos);
	dinner->print = sem_open("/print", O_CREAT, 0644, 1);
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
	ph_print_dinner(dinner);
	return (dinner);
}
