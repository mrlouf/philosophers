/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:36:58 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/22 17:51:28 by nponchon         ###   ########.fr       */
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
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
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
	pthread_t		monitor;
	pthread_t		*philos_th;
	pthread_mutex_t	init;
	pthread_mutex_t	status;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_dinner;

//	DINING
int			ph_check_args(int ac, char **av);
t_dinner	*ph_init_simulation(int ac, char **av);
int			ph_init_dinner(int ac, char **av, t_dinner *dinner);
int			ph_init_forks(t_dinner *dinner);
int			ph_init_philos(t_dinner *dinner);
int			ph_start_dinner(t_dinner *dinner);
int			ph_is_stopped(t_philo *philo);
void		ph_stop_dinner(t_dinner *dinner);
void		*ph_routine(void *i);
void		*ph_lone_philo(t_philo *philo);
void		*ph_monitor(void *data);

//	UTILS
int			ph_check_status(t_dinner *dinner);
int			ph_check_starvation(t_dinner *dinner, int i);
void		ph_delay(long long start);
time_t		ph_gettime(void);
int			ph_is_integer(const char *str);
long long	ph_atoll(const char *str);
int			ph_clean_dinner(t_dinner *dinner);
void		ph_usleep(time_t time);

//	PRINTS && DEBUG
void		ph_print_status(t_dinner *dinner, char *str, int id);
void		ph_print_complete(t_dinner *dinner);
int			ph_print_err(char *str);
int			ph_print_usage(void);
void		ph_print_dinner(t_dinner *dinner);

#endif