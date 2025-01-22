/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:29:04 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 09:32:08 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	An error message displayed in case of incorrect input.
*/
int	ph_print_usage(void)
{
	printf("Correct usage: ");
	printf("./philo ");
	printf("nb_of_philosophers (1-200) ");
	printf("time_to_die (60-INT_MAX) ");
	printf("time_to_eat (60-INT_MAX) ");
	printf("time_to_sleep (60-INT_MAX) ");
	printf("[optional: meals_per_each_philosopher (0-INT_MAX)]\n");
	return (1);
}
