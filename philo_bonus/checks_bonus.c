/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:31:18 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 09:31:34 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
