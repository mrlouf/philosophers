/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:25:30 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 09:34:20 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	dinner = NULL;
	(void)dinner;
	if (ac < 5 || ac > 6 || ph_check_args(ac - 1, av))
		return (ph_print_usage());
	printf("starting simulation\n");
	return (0);
}
