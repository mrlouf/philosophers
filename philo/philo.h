#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

int 	ph_check_args(int ac, char **av);
void	ph_init_dinner();

//	UTILS
int	ft_is_integer(const char *str);
int	ft_atoi(const char *str);

#endif