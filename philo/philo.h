/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:36:58 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/15 14:41:48 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_dinner
{
	int	guests;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	optional_meals;
	int	number_of_meals;
}	t_dinner;

//	DINING
int		ph_check_args(int ac, char **av);
void	ph_init_dinner(int ac, char **av);

//	UTILS
int		ft_is_integer(const char *str);
int		ft_atoi(const char *str);

//	DEBUG
void	ph_print_usage(void);
void	ph_print_dinner(t_dinner *dinner);

#endif