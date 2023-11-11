/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:16:48 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/11 14:10:01 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdlib.h>

void	free_everything(t_philo *philos)
{
	int		i;
	t_table	*table;

	i = -1;
	table = philos->table;
	while (i++, i < table->number_of_p)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&philos[i].mutex_w_eat);
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->mutex_break_eat);
	pthread_mutex_destroy(&table->mutex_total_meal);
	free(table->forks);
	free(philos);
}
