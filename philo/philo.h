#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_dinner
{
	int	guests;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meal;
} t_dinner;

int 	ph_check_args(int ac, char **av);
void	ph_init_dinner(int ac, char **av);

//	UTILS
int		ft_is_integer(const char *str);
int		ft_atoi(const char *str);

#endif