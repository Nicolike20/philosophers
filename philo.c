/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:31:28 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/24 18:58:36 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//TODO: intentar optimizarlo a full;
//TODO: print de thinking;
//TODO: ponerlo bonito;
//TODO: makefile;
//TODO: check that a philosopher dies and its eating at the same time?
//TODO: imprimir numero de veces que ha comido?;
//TODO: leaks?;
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

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		if (ft_atoi(argv[i]) >= 2147483648 || ft_atoi(argv[i]) <= 0)
			return (1);
		if (argv[i][0] == '\0')
			return (1);
		if (argv[i][0] == '-' && argv[i][1] == '\0')
			return (1);
		if (argv[i][0] == '-')
			j++;
		while (argv[i][++j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
		}
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	philo_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
	{
		table->philo[i].index = i + 1;
		pthread_mutex_init(&table->philo[i].fork, NULL);
		//gettimeofday(&vars->philo[i].time, NULL);
		table->philo[i].init_time = get_time();
		table->philo[i].current_time = get_time();
		table->philo[i].last_eat = get_time();
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
	if (argc == 6)
		table->it_num = ft_atoi(argv[5]) * table->philo_num;
	else
		table->it_num = -1;
	table->dead_philo = 0;
	table->times_eaten = 0;
	table->it_max = 0;
	philo = malloc(sizeof(t_philo) * table->philo_num);
	if (philo == NULL)
		fail(0);
	table->philo = philo;
	pthread_mutex_init(&table->printf_mtx, NULL);
	philo_init(table);
}

void	printf_status(t_philo *philo, int status)
{
	if (philo->table->dead_philo == 1)
		return ;
	pthread_mutex_lock(&philo->table->printf_mtx);
	printf("\e[1;36m[%5d]", (int)(get_time() - philo->init_time));
	printf("\e[1;35m Philo %2d", philo->index);
	if (status == 0) //maybe quitar;
		printf("\e[1;34m has taken a fork\e[0m\n");
	if (status == 1) //maybe quitar;
		printf("\e[1;32m is eating: %d\e[0m\n", philo->table->times_eaten);
	if (status == 2) //maybe quitar;
		printf("\e[1;33m is sleeping\e[0m\n");
	if (status == 3) //maybe quitar esto;
		printf("\e[1;95m is thinking\e[0m\n");
	if (status == 4)
		printf("\e[1;31m is dead\e[0m\n");

	pthread_mutex_unlock(&philo->table->printf_mtx);
}

void	bedtime(t_philo *philo, int check_es)
{
	if (check_es == 0)
	{
		while (1)
		{
			if ((int)(get_time() - philo->last_eat) >= philo->table->eat_time || philo->table->dead_philo == 1)
				break ;
			usleep(100);
		}
	}
	if (check_es == 1)
	{
		while (1)
		{
			if ((int)(get_time() - philo->last_sleep) >= philo->table->sleep_time || philo->table->dead_philo == 1)
				break ;
			usleep(100);
		}
	}
}

int	philo_is_dead(t_philo *philo, t_table *table)
{
	if ((int)((get_time() - philo->init_time) - (philo->last_eat - philo->init_time)) > philo->table->die_time && table->it_max == 0) //quitar los philo->init_time ?
	{
		printf_status(philo, 4);
		table->dead_philo = 1;
		return (1);
	}
	return (0);
}

void	*philo(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	while (philo->table->dead_philo == 0 && (philo->table->it_num < 0 || philo->table->times_eaten < philo->table->it_num - 1))
	{
		if (philo->index % 2 != 0)
			usleep(1000);
		pthread_mutex_lock(&philo->fork);
		printf_status(philo, 0);
		// si solo hay uno se queda aqui :/
		// if philo_num == 1 -> xd
		if (philo->table->philo_num == 1)
		{
//			pthread_mutex_unlock(&philo->fork); //leaks por tener esto comentado??
			break ;
		}
		pthread_mutex_lock(&philo->right->fork);
		printf_status(philo, 0);
		philo->last_eat = get_time();
		philo->table->times_eaten += 1;
		printf_status(philo, 1);
		bedtime(philo, 0);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->right->fork);
		philo->last_sleep = get_time();
		printf_status(philo, 2);
		bedtime(philo, 1);
		printf_status(philo, 3);
		//printf("test table: %d\n", philo->table->philo_num);
		//printf("test right: %d\n", philo->right->index);
		//printf("test time %d: %d\n", philo->index, (int)philo->time);
		//printf("dead_philo: %d\n", philo->table->dead_philo);
	}
	return (NULL);
}
void	create_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
		pthread_create(&table->philo[i].id, NULL, philo, &table->philo[i]);
	while (table->it_max == 0) // aqui pon lo de si han comido x veces
	{
		i = -1;
		while (++i < table->philo_num)
		{
			if (philo_is_dead(&table->philo[i], table))
				break ;
			usleep(100);
		}
		if (table->dead_philo == 1)
			break ;
		//while pa ver si han comido;
		i = -1;
		if (table->times_eaten == table->it_num)
			table->it_max = 1;
		/*while(++i < table->philo_num)
		{
			//printf("times_eaten: %d\n", table->philo[i].times_eaten);
			//printf("it_num: %d\n", table->it_num);
			if (table->times_eaten == table->it_num)
				table->it_max = 1;
		}*/
		/*if (table->philo[i].times_eaten == table->it_num)
			break ;*/
	}
	i = -1;
	while (++i < table->philo_num)
		pthread_join(table->philo[i].id, NULL);
	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_destroy(&table->philo[i].fork);
	pthread_mutex_destroy(&table->printf_mtx);
}

void	leaks(void)
{
	system("leaks -q a.out");
}

int	main(int argc, char **argv)
{
	t_table	table;

	//atexit(leaks);
	if (argc == 5 || argc == 6)
	{
		if (check_args(argv)) //check que no sean negativos;
		{
			fail(1);
			return (0); //return 2?
		}
		table_init(argc, argv, &table);
		//printf("test\nPhilonum: %d\nforknum: %d\ndietime: %d\neattime: %d\nsleeptime: %d\nitnum: %d\n", vars.philo_num, vars.fork_num, vars.die_time, vars.eat_time, vars.sleep_time, vars.it_num);
		create_threads(&table);
		free(table.philo);
	}
	else
		fail(1); //return 2?;
	return (0);
}
