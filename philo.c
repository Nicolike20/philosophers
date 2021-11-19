/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:31:28 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/19 18:26:11 by nortolan         ###   ########.fr       */
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

void	philo_init(int argc, char **argv, t_philo *vars)
{
	argc = 0; //quitar, solo para compilar con flags;
	vars->philo_n = ft_atoi(argv[1]); //TODO: CAMBIAR A FT_ATOI
}

int	main(int argc, char **argv)
{
	t_philo vars;
	if (argc == 5 || argc == 6)
	{
		if (check_args(argv)) //check que no sean negativos;
			fail(1);
		philo_init(argc, argv, &vars);
		printf("Todo bien\n");
	}
	else
		fail(1);
	return (0);
}
