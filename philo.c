/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:31:28 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/22 18:40:45 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fail(int i)
{
	if (i == 0)
		write(2, "Error\n", 6);
	if (i == 1)
		write(2, "Invalid arguments\n", 18);
	exit(2);
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
	struct timezone	tzp;

	gettimeofday(&tp, &tzp);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	philo_init(t_table *vars)
{
	int	i;

	i = -1;
	while (++i < vars->philo_num)
	{
		vars->philo[i].index = i + 1;
		pthread_mutex_init(&vars->philo[i].fork, NULL);
		//gettimeofday(&vars->philo[i].time, NULL);
		vars->philo[i].time = get_time();
		vars->philo[i].table = vars;
		vars->philo[i].right = &vars->philo[i + 1];
	}
	vars->philo[i - 1].right = &vars->philo[0];
}

void	mesa_init(int argc, char **argv, t_table *vars)
{
	t_philo	*philo;

	vars->philo_num = ft_atoi(argv[1]);
	vars->fork_num = vars->philo_num;
	vars->die_time = ft_atoi(argv[2]);
	vars->eat_time = ft_atoi(argv[3]);
	vars->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		vars->it_num = ft_atoi(argv[5]);
	else
		vars->it_num = -1;
	philo = malloc(sizeof(t_philo) * vars->philo_num);
	if (philo == NULL)
		fail(0);
	vars->philo = philo;
	philo_init(vars);
}

void	*philo(void *test)
{
	t_philo	*philo;

	philo = (t_philo *)test;
	if (philo->index % 2 != 0)
		usleep(1000);
	printf("test: %d\n", philo->index);
	//printf("test table: %d\n", philo->table->philo_num);
	//printf("test right: %d\n", philo->right->index);
	printf("test time %d: %d\n", philo->index, (int)philo->time);
	return (NULL);
}

void	create_threads(t_table *vars)
{
	int	i;

	i = -1;
	while (++i < vars->philo_num)
	{
		pthread_create(&vars->philo[i].id, NULL, philo, &vars->philo[i]);
	}
	i = -1;
	while (++i < vars->philo_num)
	{
		pthread_join(vars->philo[i].id, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_table	vars;
	if (argc == 5 || argc == 6)
	{
		if (check_args(argv)) //check que no sean negativos;
			fail(1);
		mesa_init(argc, argv, &vars);
		printf("test\nPhilonum: %d\nforknum: %d\ndietime: %d\neattime: %d\nsleeptime: %d\nitnum: %d\n", vars.philo_num, vars.fork_num, vars.die_time, vars.eat_time, vars.sleep_time, vars.it_num);
		create_threads(&vars);
	}
	else
		fail(1);
	return (0);
}
