#include "philo.h"

/*
    Checks that all the arguments are positive, valid integers,
    and that av[0] (the number of philos) is within 1-200 range.
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
        else if (tmp < 60 || tmp > INT_MAX)
            return (1);
    }
    return (0);
}

void    ph_start_dinner(t_dinner *dinner)
{
    printf("");
}

void    ph_init_dinner(int ac, char **av)
{
    t_dinner    dinner;

    dinner.guests = av[1];
    dinner.time_to_die = av[2];
    dinner.time_to_eat = av[3];
    dinner.time_to_sleep = av[4];
    if (ac = 6)
        dinner.number_of_meal = av[5];
    else
        dinner.number_of_meal = NULL;
    ph_start_dinner(&dinner);
}

int main(int ac, char **av)
{
    if (ac >= 5 && ac <= 6 && !ph_check_args(ac - 1, av))
        ph_init_dinner(ac, av);
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
