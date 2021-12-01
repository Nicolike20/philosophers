/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:21 by nortolan          #+#    #+#             */
/*   Updated: 2021/12/02 00:38:09 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
	{
		table->philo[i].index = i + 1;
		pthread_mutex_init(&table->philo[i].fork, NULL);
		table->philo[i].init_time = get_time();
		table->philo[i].current_time = get_time();
		table->philo[i].last_eat = get_time();
		table->philo[i].philo_times_eaten = 0;
		table->philo[i].table = table;
		table->philo[i].right = &table->philo[i + 1];
	}
	table->philo[i - 1].right = &table->philo[0];
}

void	table_init(int argc, char **argv, t_table *table)
{
	t_philo	*philo;

	table->philo_num = ft_atoi(argv[1]);
	table->fork_num = table->philo_num;
	table->die_time = ft_atoi(argv[2]);
	table->eat_time = ft_atoi(argv[3]);
	table->sleep_time = ft_atoi(argv[4]);
	table->it_num = -1;
	if (argc == 6)
		table->it_num = ft_atoi(argv[5]) * table->philo_num;
	table->single_it_num = -1;
	if (argc == 6)
		table->single_it_num = ft_atoi(argv[5]);
	table->dead_philo = 0;
	table->total_times_eaten = 0;
	table->it_max = 0;
	philo = malloc(sizeof(t_philo) * table->philo_num);
	if (philo == NULL)
		fail(0);
	table->philo = philo;
	pthread_mutex_init(&table->eat_mtx, NULL);
	pthread_mutex_init(&table->printf_mtx, NULL);
	pthread_mutex_init(&table->die_check_mtx, NULL);
	philo_init(table);
}
