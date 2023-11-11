/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 02:32:23 by enveryilmaz       #+#    #+#             */
/*   Updated: 2023/11/11 20:26:06 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"
#include <stdio.h>

int	check_die_loop(t_table *t, int i, int number_philo)
{
	while (i < number_philo)
	{
		sem_wait(t->p[i].sem_time_last_eat);
		if (get_time() - t->p[i].time_last_eat >= t->time_die)
		{
			my_printf(t, &t->p[i], "\033[0;31mphilo is dead\033[0;0m\n");
			sem_post(t->p[i].sem_time_last_eat);
			if (number_philo == 1)
				sem_post(t->sem_forks);
			sem_wait(t->sem_is_die);
			t->is_die = 1;
			sem_post(t->sem_is_die);
			return (0);
		}
		sem_post(t->p[i].sem_time_last_eat);
		i++;
	}
	return (1);
}

void	*check_die(void *arg)
{
	t_table	*t;
	int		number_philo;

	t = (t_table *)arg;
	sem_wait(t->sem_number_of_p);
	number_philo = t->number_of_p;
	sem_post(t->sem_number_of_p);
	while (1)
	{
		if (t->p[0].must_least_eat != -1
			&& t->total_eat / number_philo >= t->p[0].must_least_eat)
			return (NULL);
		if (!check_die_loop(t, 0, number_philo))
			return (NULL);
		ft_usleep(10);
	}
	return (NULL);
}
