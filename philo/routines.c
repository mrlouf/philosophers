/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:28:02 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 13:26:38 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_monitor(void *data)
{
	(void)data;
	printf("Monitor finished\n");
	return (NULL);
}

/*
	The dining routine for each philosopher: eat, think, sleep, repeat.
	TODO
	- implement the routine
*/
void	*ph_routine(void *data)
{
	(void)data;
	printf("Philosopher (thread) #%i created\n", 1);
	return (NULL);
}
