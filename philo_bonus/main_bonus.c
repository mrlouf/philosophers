/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:25:30 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 18:56:42 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	Cleans the program by closing, then unlinking the semaphors created.
	Frees the pointers.
	Hint: check for leaking semaphors with 'ls /dev/shm'
*/
int	ph_clean_dinner(t_dinner *dinner)
{
	sem_close(dinner->forks);
	sem_unlink("/forks");
	sem_close(dinner->print);
	sem_unlink("/print");
	free(dinner->philos);
	free(dinner);
	return (0);
}

int	ph_start_simulation(t_dinner *dinner)
{
	int	i;

	i = -1;
	dinner->start = ph_gettime() + (dinner->nb_philos * 20);
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i].pid = fork();
		if (dinner->nb_philos == 1 && dinner->philos[i].pid == 0)
			ph_lone_philo(&dinner->philos[i]);
		else if (dinner->philos[i].pid == 0)
			ph_routine(&dinner->philos[i]);
		else if (dinner->philos[i].pid < 0)
			return (ph_print_err("Error forking philos"));
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (0);
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	dinner = NULL;
	if (ac < 5 || ac > 6 || ph_check_args(ac - 1, av))
		return (ph_print_usage());
	dinner = ph_init_simulation(ac, av);
	if (ph_start_simulation(dinner))
		return (EXIT_FAILURE);
	ph_clean_dinner(dinner);
	return (EXIT_SUCCESS);
}
