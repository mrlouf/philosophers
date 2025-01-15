/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:34:53 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/15 14:41:57 by nponchon         ###   ########.fr       */
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
		if (!ft_is_integer(av[i]))
			return (1);
		tmp = ft_atoi(av[i]);
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
	ph_print_dinner(dinner);
}

void	ph_init_dinner(int ac, char **av)
{
	t_dinner	dinner;

	dinner.guests = ft_atoi(av[1]);
	dinner.time_to_die = ft_atoi(av[2]);
	dinner.time_to_eat = ft_atoi(av[3]);
	dinner.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		dinner.optional_meals = 1;
		dinner.number_of_meals = ft_atoi(av[5]);
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
