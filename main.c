/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:40:53 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/29 18:22:34 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **argv)
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

/*void	leaks(void)
{
	system("leaks -q philo");
}*/
/*	atexit(leaks);*/

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (check_args(argv))
		{
			fail(1);
			return (EXIT_FAILURE);
		}
		table_init(argc, argv, &table);
		create_threads(&table);
		free(table.philo);
	}
	else
	{
		fail(1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
