/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:05:53 by enveryilmaz       #+#    #+#             */
/*   Updated: 2023/11/11 20:27:38 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>

char	*my_join(int i)
{
	char	c;
	char	c2;
	char	c3;
	char	*str;

	c = (i / 100) + 48;
	c2 = ((i / 10) % 10) + 48;
	c3 = (i % 10) + 48;
	str = (char *)malloc(sizeof(char) * 6);
	if (!str)
		return (NULL);
	str[0] = 's';
	str[1] = 'e';
	str[2] = 'm';
	str[3] = c;
	str[4] = c2;
	str[4] = c3;
	str[5] = '\0';
	return (str);
}

int	set_philo_sem(t_philo *p, int i)
{
	p->name_of_sem = my_join(i);
	if (!p->name_of_sem)
		return (0);
	sem_unlink(p->name_of_sem);
	p->sem_time_last_eat = sem_open(p->name_of_sem, O_CREAT, 0666, 1);
	if (p->sem_time_last_eat == SEM_FAILED)
		return (free(p->name_of_sem), 0);
	return (1);
}

int	set_philos(t_table *t, char **av)
{
	int	i;

	i = 0;
	while (i < t->number_of_p)
	{
		t->p[i].id = i + 1;
		t->p[i].time_eat = ft_atoi(av[3]);
		t->p[i].time_sleep = ft_atoi(av[4]);
		t->p[i].num_eat = 0;
		t->p[i].must_least_eat = -1;
		if (av[5])
			t->p[i].must_least_eat = ft_atoi(av[5]);
		t->p[i].table = t;
		if (!set_philo_sem(&t->p[i], i))
		{
			if (i == 0)
				return (0);
			return (free_value_in_philos(t, i), 0);
		}
		i++;
	}
	return (1);
}
