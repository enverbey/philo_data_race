/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:24:43 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/11 18:28:30 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

/*
void	free_and_unlock(t_table *t, t_philo *p)
{
	sem_close(p->sem_time_last_eat);//
	sem_unlink(p->name_of_sem);//
	free(p->name_of_sem);//
}
*/

void	start_life(t_table *t)
{
	int			i;
	pthread_t	*id;
	pthread_t	check;

	id = (pthread_t *)malloc(sizeof(pthread_t) * t->number_of_p);
	i = 0;
	t->start_time = get_time();
	while (i < t->number_of_p)
	{
		t->p[i].time_last_eat = t->start_time;
		pthread_create(&id[i], NULL, life, (void *)&t->p[i]);
		i++;
	}
	pthread_create(&check, NULL, check_die, (void *)t);
	i = 0;
	while (i < t->number_of_p)
	{
		pthread_join(id[i], NULL);
		i++;
	}
	pthread_join(check, NULL);
	free(id);
	free_table_and_philos(t);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!checker_philo_av(ac, av))
		return (printf("Error\n"), 1);
	if (!set_table(&table, av))
		return (printf("Error\n"), 1);
	if (!set_philos(&table, av))
		return (printf("Error\n"), free_value_in_table(&table), 1);
	start_life(&table);
	return (0);
}
