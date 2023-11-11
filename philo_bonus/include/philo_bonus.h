/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:45:41 by envyilma          #+#    #+#             */
/*   Updated: 2023/11/11 20:29:11 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				must_least_eat;
	char			*name_of_sem;
	sem_t			*sem_time_last_eat;
	u_int64_t		time_last_eat;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				stop;
	t_philo			*p;
	pid_t			*pid;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_total_eat;
	sem_t			*sem_number_of_p;
	sem_t			*sem_is_die;
	u_int64_t		start_time;
	u_int64_t		time_die;
	int				is_die;
	int				number_of_p;
	int				total_eat;
}					t_table;

//-> checker
int			checker_philo_av(int ac, char **av);
int			check_int(char **s);

//-> get time
u_int64_t	get_time(void);

//-> libft
int			ft_atoi(char *str);
int			ft_usleep(useconds_t time);

//->
void		*life(void *arg);
void		*check_die(void *arg);
void		my_printf(t_table *t, t_philo *p, char *str);

//->sets
int			set_table(t_table *t, char **av);
int			set_philos(t_table *t, char **av);

//free
void		free_value_in_table(t_table *t);
void		free_value_in_philos(t_table *t, int i);
void		free_table_and_philos(t_table *t);

#endif