/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:36:58 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/17 13:40:54 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_dinner	t_dinner;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	t_dinner		*dinner;
}	t_philo;

typedef struct s_dinner
{
	int				nb_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int				dead_philo;
	long long		start;
	pthread_t		monitor;
	pthread_t		*philos_th;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_dinner;

//	DINING
int		ph_check_args(int ac, char **av);
int		ph_init_simulation(int ac, char **av);
void	ph_init_dinner(int ac, char **av, t_dinner *dinner);
int		ph_init_forks(t_dinner *dinner);
int		ph_init_philos(t_dinner *dinner);
int		ph_start_dinner(t_dinner *dinner);
void	*ph_routine(void *i);
void	*ph_monitor(void *data);

//	UTILS
int		ph_is_integer(const char *str);
int		ph_atoll(const char *str);
int		ph_print_err(char *str);

//	PRINTS && DEBUG
void	ph_print_tod(void);
void	ph_print_usage(void);
void	ph_print_dinner(t_dinner *dinner);

#endif