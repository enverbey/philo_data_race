/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:27:40 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/11 20:29:04 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"
#include <stdlib.h>

static void	error_free_philos(t_table *t, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		sem_close(t->p[i].sem_time_last_eat);
		sem_unlink(t->p[i].name_of_sem);
		free(t->p[i].name_of_sem);
		i++;
	}
}

void	free_value_in_philos(t_table *t, int i)
{
	if (!i)
		error_free_philos(t, t->number_of_p);
	else
		error_free_philos(t, i);
}

void	free_table_and_philos(t_table *t)
{
	error_free_philos(t, t->number_of_p);
	free_value_in_table(t);
}
