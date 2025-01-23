/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:26:30 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/23 10:16:58 by nponchon         ###   ########.fr       */
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
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

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
	pid_t			pid;
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
	sem_t			*forks;
	sem_t			*status;
	sem_t			*print;
	t_philo			*philos;
}	t_dinner;

//	DINING
int			ph_check_args(int ac, char **av);
t_dinner	*ph_init_simulation(int ac, char **av);
int			ph_init_sems(t_dinner *dinner);
int			ph_init_philos(t_dinner *dinner);
int			ph_start_simulation(t_dinner *dinner);
int			ph_clean_dinner(t_dinner *dinner);
void		ph_routine(t_philo *philo);
void		ph_lone_philo(t_philo *philo);

//	UTILS
time_t		ph_gettime(void);
void		ph_sleep(time_t time);
void		ph_delay(long long start);
int			ph_is_integer(const char *str);
long long	ph_atoll(const char *str);

//	PRINTS && DEBUG
void		ph_print_complete(t_dinner *dinner);
int			ph_print_usage(void);
void		ph_print_dinner(t_dinner *dinner);
int			ph_print_err(char *str);
void		ph_print_status(t_dinner *dinner, char *str, int id);

#endif