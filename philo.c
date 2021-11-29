/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:31:28 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/29 18:27:57 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//TODO: ENTREGAR SIN README;
//TODO: intentar optimizarlo a full;
static void	bedtime(t_philo *philo, int check_es)
{
	if (check_es == 0)
	{
		while (1)
		{
			if ((int)(get_time() - philo->last_eat)
				>= philo->table->eat_time || philo->table->dead_philo == 1)
				break ;
			usleep(100);
		}
	}
	if (check_es == 1)
	{
		while (1)
		{
			if ((int)(get_time() - philo->last_sleep)
				>= philo->table->sleep_time || philo->table->dead_philo == 1)
				break ;
			usleep(100);
		}
	}
}

static void	philo_aux(t_philo *philo)
{
	pthread_mutex_lock(&philo->right->fork);
	printf_status(philo, 0);
	pthread_mutex_lock(&philo->table->eat_mtx);
	philo->last_eat = get_time();
	philo->table->total_times_eaten += 1;
	philo->philo_times_eaten += 1;
	printf_status(philo, 1);
	pthread_mutex_unlock(&philo->table->eat_mtx);
	bedtime(philo, 0);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->right->fork);
	philo->last_sleep = get_time();
	printf_status(philo, 2);
	bedtime(philo, 1);
	printf_status(philo, 3);
}

static void	*philo(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	while (philo->table->dead_philo == 0 && (philo->table->it_num < 0
			|| philo->table->total_times_eaten < philo->table->it_num - 1))
	{
		if (philo->index % 2 != 0)
			usleep(1000);
		pthread_mutex_lock(&philo->fork);
		printf_status(philo, 0);
		if (philo->table->philo_num == 1)
			break ;
		philo_aux(philo);
	}
	return (NULL);
}

static void	create_threads_aux(t_table *table, int i)
{
	i = -1;
	while (++i < table->philo_num)
	{
		pthread_mutex_lock(&table->die_check_mtx);
		if (philo_is_dead(&table->philo[i], table))
			break ;
		pthread_mutex_unlock(&table->die_check_mtx);
		usleep(100);
	}
}

void	create_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
		pthread_create(&table->philo[i].id, NULL, philo, &table->philo[i]);
	while (table->it_max == 0)
	{
		create_threads_aux(table, i);
		if (table->dead_philo == 1)
			break ;
		i = -1;
		if (table->total_times_eaten == table->it_num)
			table->it_max = 1;
	}
	i = -1;
	while (++i < table->philo_num)
		pthread_join(table->philo[i].id, NULL);
	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_destroy(&table->philo[i].fork);
	pthread_mutex_destroy(&table->printf_mtx);
	pthread_mutex_destroy(&table->eat_mtx);
	pthread_mutex_destroy(&table->die_check_mtx);
}
