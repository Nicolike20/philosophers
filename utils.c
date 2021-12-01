/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:46:26 by nortolan          #+#    #+#             */
/*   Updated: 2021/12/02 00:37:15 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fail(int i)
{
	if (i == 0)
		write(2, "Error\n", 6);
	if (i == 1)
		write(2, "Invalid arguments\n", 18);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	s;
	long	nb;

	i = 0;
	s = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			s = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * s);
}

size_t	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	printf_status(t_philo *philo, int status)
{
	pthread_mutex_lock((pthread_mutex_t *)&philo->table->printf_mtx);
	if (philo->table->dead_philo == 1 || philo->table->it_max == 1)
	{
		pthread_mutex_unlock((pthread_mutex_t *)&philo->table->printf_mtx);
		return ;
	}
	printf("\e[2;36m[%5d]\e[0m", (int)(get_time() - philo->init_time));
	if (status == 0)
		printf("\e[1;93m\e[2;34m Philo\e[0m\e[1;93m %2d\e[2;34m"
			" has taken a fork 箸🥢\e[0m\n", philo->index);
	if (status == 1)
		printf("\e[1;32m Philo\e[1;33m %2d\e[1;32m is eating 食🍜 #%d\e[0m\n",
			philo->index, philo->philo_times_eaten);
	if (status == 2)
		printf("\e[1;36m Philo\e[1;33m %2d\e[1;36m is sleeping 寝💤\e[0m\n",
			philo->index);
	if (status == 3)
		printf("\e[1;35m Philo\e[1;33m %2d\e[1;35m is thinking 思🤔\e[0m\n",
			philo->index);
	if (status == 4)
		printf("\e[1;31m Philo\e[1;33m %2d\e[1;31m is dead 死💀\e[0m\n",
			philo->index);
	pthread_mutex_unlock((pthread_mutex_t *)&philo->table->printf_mtx);
}

int	philo_is_dead(t_philo *philo, t_table *table)
{
	if ((int)((get_time() - philo->init_time) - (philo->last_eat
			- philo->init_time)) > philo->table->die_time && table->it_max == 0)
	{
		printf_status(philo, 4);
		table->dead_philo = 1;
		return (1);
	}
	return (0);
}
