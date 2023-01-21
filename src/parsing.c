/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajani <mmajani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 15:48:16 by mmajani           #+#    #+#             */
/*   Updated: 2023/01/21 16:07:07 by mmajani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_positive_int(int ac, char **av)
{
	int	i;
	int	s;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' || (my_atoi(av[i]) == 0 && i != 0) ||
			(my_atoi(av[i]) < 1 && i == 0))
			return (0);
		if (ft_isnum(av[i]) == -1)
			return (0);
		s = ft_strlen(av[i]);
		if (av[i][0] != '-')
		{
			if (s > 10 || (s == 10 && ft_strcmp(av[i], "2147483647") > 0))
				return (0);
		}
		else if (s > 11 || (s == 11 && ft_strcmp(av[i], "-2147483648") > 0))
			return (0);
		i++;
	}
	return (1);
}

void	parse_data(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac - 1)
	{
		data->args[i] = my_atoi(av[i + 1]);
		i++;
	}
}

int	parser_main(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Invalid number of arguments\n");
		return (-1);
	}
	if (is_positive_int(ac, av) == 1)
		parse_data(data, ac, av);
	else
	{
		printf("Invalid arguments\n");
		return (-1);
	}
	return (1);
}
