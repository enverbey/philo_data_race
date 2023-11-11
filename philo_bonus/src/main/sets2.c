/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:26:21 by enveryilmaz       #+#    #+#             */
/*   Updated: 2023/11/11 20:30:27 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"
#include <stdlib.h>

void	free_value_in_table(t_table *t)
{
	sem_close(t->sem_forks);
	sem_unlink("./sem_forks");
	sem_close(t->sem_print);
	sem_unlink("./sem_print");
	sem_close(t->sem_total_eat);
	sem_unlink("./sem_total_eat");
	sem_close(t->sem_total_eat);
	sem_unlink("./sem_total_eat");
	sem_close(t->sem_is_die);
	sem_unlink("./sem_is_die");
	free(t->p);
	free(t->pid);
}

int	set_table_cont2(t_table *t)
{
	if (t->sem_number_of_p == SEM_FAILED)
		return (free(t->p), free(t->pid),
			sem_close(t->sem_forks), sem_unlink("./sem_forks"),
			sem_close(t->sem_print), sem_unlink("./sem_print"),
			sem_close(t->sem_total_eat), sem_unlink("./sem_total_eat"), 0);
	t->sem_is_die = sem_open("./sem_is_die", O_CREAT, 0666, 1);
	if (t->sem_is_die == SEM_FAILED)
		return (free(t->p), free(t->pid),
			sem_close(t->sem_forks), sem_unlink("./sem_forks"),
			sem_close(t->sem_print), sem_unlink("./sem_print"),
			sem_close(t->sem_total_eat), sem_unlink("./sem_total_eat"),
			sem_close(t->sem_is_die), sem_unlink("./sem_is_die"), 0);
	return (1);
}

int	set_table_cont(t_table *t)
{
	t->sem_forks = sem_open("./sem_forks", O_CREAT, 0666, t->number_of_p);
	if (t->sem_forks == SEM_FAILED)
		return (free(t->p), free(t->pid), 0);
	t->sem_print = sem_open("./sem_print", O_CREAT, 0666, 1);
	if (t->sem_print == SEM_FAILED)
		return (free(t->p), free(t->pid),
			sem_close(t->sem_forks), sem_unlink("./sem_forks"), 0);
	t->sem_total_eat = sem_open("./sem_total_eat", O_CREAT, 0666, 1);
	if (t->sem_total_eat == SEM_FAILED)
		return (free(t->p), free(t->pid),
			sem_close(t->sem_forks), sem_unlink("./sem_forks"),
			sem_close(t->sem_print), sem_unlink("./sem_print"), 0);
	t->sem_number_of_p = sem_open("./sem_number_of_p", O_CREAT, 0666, 1);
	return (set_table_cont2(t));
}

int	set_table(t_table *t, char **av)
{
	t->is_die = 0;
	t->stop = 0;
	t->total_eat = 0;
	t->number_of_p = ft_atoi(av[1]);
	t->time_die = (u_int64_t)ft_atoi(av[2]);
	t->p = (t_philo *)malloc(sizeof(t_philo) * t->number_of_p);
	if (!t->p)
		return (0);
	t->pid = (pid_t *)malloc(sizeof(pid_t) * t->number_of_p);
	if (!t->pid)
		return (free(t->p), 0);
	sem_unlink("./sem_forks");
	sem_unlink("./sem_print");
	sem_unlink("./sem_total_eat");
	sem_unlink("./sem_number_of_p");
	return (set_table_cont(t));
}
