#include "philo.h"

int ph_check_args(int ac, char **av)
{
    int i;

    i = -1;
    while (++i < ac)
    {
        
    }
}

int main(int ac, char **av)
{
    (void)av;
    if (ac >= 5 && ac <= 6 && ph_check_args(ac, av))
        ph_start_dinner();
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
