/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:36:58 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 07:50:12 by nponchon         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t	fork;
}	t_philo;

typedef struct s_dinner
{
	int		nb_guests;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		optional_meals;
	int		number_of_meals;
	t_philo	*guests;
}	t_dinner;

//	DINING
int		ph_check_args(int ac, char **av);
void	ph_init_dinner(int ac, char **av);
void	*ph_routine(void *i);

//	UTILS
int		ph_is_integer(const char *str);
int		ph_atoll(const char *str);

//	PRINTS && DEBUG
void	ph_print_usage(void);
void	ph_print_dinner(t_dinner *dinner);

#endif