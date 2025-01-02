#include "philo.h"

int main(int ac, char **av)
{
    (void)av;
    if (ac >= 5 && ac <= 6)
    {
        printf("execute program\n");
    }
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
