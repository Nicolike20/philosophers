/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:32:02 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/23 17:10:49 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		id;
	int				index;
	pthread_mutex_t	fork;
	size_t	init_time;
	size_t	current_time;
	size_t	last_eat;
	struct s_philo	*right;
	struct s_table	*table;
}t_philo;

typedef struct s_table
{
	int		philo_num;
	int		fork_num;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		dead_philo;
	int		it_num;
	t_philo	*philo;
}t_table;

#endif
