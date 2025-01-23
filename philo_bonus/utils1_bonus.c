/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:32:46 by nponchon          #+#    #+#             */
/*   Updated: 2025/01/23 12:59:33 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	Generates a unique name for the semaphore with the philo id so that:
	philo[N].sem = "/counterN"
*/
char	*ph_get_sem_name(char *str, int i)
{
	char	*name;
	char	*pid;

	pid = ft_itoa(i);
	name = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(pid) + 1));
	if (!name)
		return (NULL);
	strcpy(name, str);
	strcat(name, pid);
	free(pid);
	return (name);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	intlen(int n)
{
	int		l;

	l = 1;
	if (n < 0)
		l++;
	while ((n / 10) != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = intlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (len > 0)
	{
		str[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	if (str[len] != '-')
		str[len] = (n % 10) + '0';
	return (str);
}
