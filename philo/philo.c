#include "philo.h"

/*
    Checks that all the arguments are positive, valid integers,
    and non-null for av[0] (the number of philos).
*/
int ph_check_args(int ac, char **av)
{
    int i;
    int tmp;

    i = -1;
    av++;
    while (++i < ac)
    {
        if (!ft_is_integer(av[i]))
            return (1);
        tmp = ft_atoi(av[i]);
        if (!i && (tmp < 1 || tmp > 200))
            return (1);
        else if (tmp < 0 || tmp > INT_MAX)
            return (1);
    }
    return (0);
}

void    ph_init_dinner()
{
    printf("Starting dinner\n");
}

int main(int ac, char **av)
{
    if (ac >= 5 && ac <= 6 && !ph_check_args(ac - 1, av))
        ph_init_dinner();
    else
    {
        printf("Correct usage: ");
        printf("./philo ");
        printf("number_of_philosopher ");
        printf("time_to_die ");
        printf("time_to_eat ");
        printf("time_to_sleep ");
        printf("[optional: number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    return (0);
}
