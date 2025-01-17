/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:34:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 07:58:30 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    Checks that all the arguments are positive, valid integers,
    and that av[0] (the number of philos) is within 1-200 range.
*/
int	ph_check_args(int ac, char **av)
{
	int	i;
	int	tmp;

	i = -1;
	av++;
	while (++i < ac)
	{
		if (!ph_is_integer(av[i]))
			return (1);
		tmp = ph_atoll(av[i]);
		if (!i && (tmp < 1 || tmp > 200))
			return (1);
		else if (i == 4 && (tmp < 0 || tmp > INT_MAX))
			return (1);
		else if (i && i < 4 && (tmp < 60 || tmp > INT_MAX))
			return (1);
	}
	return (0);
}

void	ph_start_dinner(t_dinner *dinner)
{
	int	i;

	ph_print_dinner(dinner);
	dinner->guests = (t_philo *)malloc(sizeof(t_philo) * dinner->nb_guests);
	if (!dinner->guests)
		return ;
	i = -1;
	while (++i < dinner->nb_guests)
	{
		if (pthread_create (&dinner->guests[i].fork, 0, ph_routine, &i))
			return ;
	}
	sleep(1);
	free(dinner->guests);
}

void	*ph_routine(void *p_data)
{
	size_t	i;

	i = (size_t)p_data;
	printf("Philosopher (thread) #%lu created\n", i);
	return (p_data);
}

void	ph_init_dinner(int ac, char **av)
{
	t_dinner	dinner;

	dinner.nb_guests = ph_atoll(av[1]);
	dinner.guests = NULL;
	dinner.time_to_die = ph_atoll(av[2]);
	dinner.time_to_eat = ph_atoll(av[3]);
	dinner.time_to_sleep = ph_atoll(av[4]);
	if (ac == 6)
	{
		dinner.optional_meals = 1;
		dinner.number_of_meals = ph_atoll(av[5]);
	}
	else
	{
		dinner.optional_meals = 0;
		dinner.number_of_meals = 0;
	}
	ph_start_dinner(&dinner);
}

int	main(int ac, char **av)
{
	if (ac >= 5 && ac <= 6 && !ph_check_args(ac - 1, av))
		ph_init_dinner(ac, av);
	else
	{
		ph_print_usage();
		return (1);
	}
	return (0);
}
