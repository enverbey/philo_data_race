/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enveryilmaz <enveryilmaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:40:53 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/06 23:18:21 by enveryilmaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"
#include <stdio.h>

int	is_number(char c, int flag)
{
	if (flag == 0 && c == '0')
		return (0);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_number(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i][j] == '+' && is_number(s[i][j + 1], 0))
			j++;
		while (s[i][j])
		{
			if (!is_number(s[i][j], j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	checker_philo_av(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf("\033[0;31mEnter 5 or 6 argumen\n\033[0;0m"), 0);
	if (!check_number(++av))
		return (printf("\033[0;31mWrong arguments\n\033[0;0m"), 0);
	if (!check_int(av))
		return (printf("\033[0;31mArguments should int\n\033[0;0m"), 0);
	if (ft_atoi(av[0]) > 200)
		return (printf("\033[0;36mless then 200 philo\n\033[0;0m"), 0);
	if (ft_atoi(av[1]) < 60 || ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60)
		return (printf("\033[0;36mmore then 60 for \
			eating, sleeping and die time\n\033[0;0m"), 0);
	return (1);
}
