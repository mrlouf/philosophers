/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:25:30 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 11:21:19 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	Cleans the program by closing, then unlinking the semaphors created.
	Frees the pointers.
	Hint: check for leaking semaphors with 'ls /dev/shm'
*/
static int	ph_clean_dinner(t_dinner *dinner)
{
	sem_close(dinner->forks);
	sem_unlink("/forks");
	sem_close(dinner->print);
	sem_unlink("/print");
	free(dinner->philos);
	free(dinner);
	return (0);
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	dinner = NULL;
	if (ac < 5 || ac > 6 || ph_check_args(ac - 1, av))
		return (ph_print_usage());
	dinner = ph_init_simulation(ac, av);
	ph_clean_dinner(dinner);
	return (0);
}
