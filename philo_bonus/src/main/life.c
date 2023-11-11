/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:04:10 by enveryilmaz       #+#    #+#             */
/*   Updated: 2023/11/11 20:26:40 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

void	my_printf(t_table *t, t_philo *p, char *str)
{
	sem_wait(t->sem_print);
	sem_wait(t->sem_is_die);
	if (!t->is_die)
		printf("%llu %d. %s", get_time() - t->start_time, p->id, str);
	sem_post(t->sem_is_die);
	sem_post(t->sem_print);
}

void	life_sem(t_table *t, t_philo *p)
{
	sem_wait(t->sem_forks);
	my_printf(t, p, "\033[0;36mphilo has taken a fork\033[0;0m\n");
	sem_wait(t->sem_forks);
	my_printf(t, p, "\033[0;36mphilo has taken a fork\033[0;0m\n");
	my_printf(t, p, "\033[0;33mphilo is eating\033[0;0m\n");
	sem_wait(p->sem_time_last_eat);
	p->time_last_eat = get_time();
	sem_post(p->sem_time_last_eat);
	sem_wait(t->sem_total_eat);
	t->total_eat++;
	sem_post(t->sem_total_eat);
	ft_usleep(p->time_eat);
	p->num_eat++;
	sem_post(t->sem_forks);
	sem_post(t->sem_forks);
	my_printf(t, p, "\033[0;32mphilo is sleeping\033[0;0m\n");
	ft_usleep(p->time_sleep);
	my_printf(t, p, "\033[0;35mphilo is thinking\033[0;0m\n");
}

int	life_loop(t_table *t, t_philo *p, int number_philo)
{
	while (1)
	{
		sem_wait(t->sem_is_die);
		if (t->is_die == 1)
		{
			sem_post(t->sem_is_die);
			return (0);
		}
		sem_post(t->sem_is_die);
		sem_wait(t->sem_total_eat);
		if (t->total_eat / number_philo < p->num_eat)
		{
			sem_post(t->sem_total_eat);
			ft_usleep(5);
		}
		else
		{
			sem_post(t->sem_total_eat);
			break ;
		}
	}
	return (1);
}

void	*life(void *arg)
{
	t_table	*t;
	t_philo	*p;
	int		number_philo;

	p = (t_philo *)arg;
	t = (t_table *)p->table;
	sem_wait(t->sem_number_of_p);
	number_philo = t->number_of_p;
	sem_post(t->sem_number_of_p);
	if (p->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (p->must_least_eat != -1 && p->num_eat >= p->must_least_eat)
			return (NULL);
		if (!life_loop(t, p, number_philo))
			return (NULL);
		life_sem(t, p);
	}
}
