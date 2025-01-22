/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:26:30 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 09:30:43 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//	MACROS

# define TAKEN_FORK "has taken a fork 🍴"
# define IS_EATING "is eating 🍝"
# define IS_SLEEPING "is sleeping 😴"
# define IS_THINKING "is thinking 💡"
# define HAS_DIED "has died 💀"

//	STRUCTURES

typedef struct s_dinner	t_dinner;

typedef struct s_philo
{
	int				id;
	int				is_alive;
	long long		meals;
	long long		last_meal;
	t_dinner		*dinner;
}	t_philo;

typedef struct s_dinner
{
	int				nb_philos;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				n_meals;
	int				live_philos;
	int				completed;
	long long		start;
	t_philo			*philos;
}	t_dinner;

//	DINING
int			ph_check_args(int ac, char **av);

//	UTILS
int			ph_is_integer(const char *str);
long long	ph_atoll(const char *str);

//	PRINTS && DEBUG
int			ph_print_usage(void);

#endif