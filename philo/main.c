/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:05:06 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 12:37:12 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac >= 5 && ac <= 6 && !ph_check_args(ac - 1, av))
		return (ph_init_simulation(ac, av));
	else
	{
		ph_print_usage();
		return (1);
	}
	return (0);
}
