/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:32:02 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/29 18:16:50 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo {
	pthread_t		id;
	int				index;
	pthread_mutex_t	fork;
	size_t			init_time;
	size_t			current_time;
	size_t			last_eat;
	size_t			last_sleep;
	struct s_philo	*right;
	int				philo_times_eaten;
	struct s_table	*table;
}	t_philo;

typedef struct s_table {
	int				philo_num;
	int				fork_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				dead_philo;
	int				it_num;
	int				total_times_eaten;
	int				it_max;
	pthread_mutex_t	printf_mtx;
	pthread_mutex_t	eat_mtx;
	pthread_mutex_t	die_check_mtx;
	t_philo			*philo;
}	t_table;

/*UTILS.C*/
void	fail(int i);
long	ft_atoi(const char *str);
size_t	get_time(void);
void	printf_status(t_philo *philo, int status);
int		philo_is_dead(t_philo *philo, t_table *table);

/*INITS.C*/
void	table_init(int argc, char **argv, t_table *table);

/*PHILO.C*/
void	create_threads(t_table *table);

#endif
