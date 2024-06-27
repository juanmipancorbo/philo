/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:14:12 by jpancorb          #+#    #+#             */
/*   Updated: 2024/06/27 13:44:21 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	atol_check(char *str)
{
	size_t	i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = (result * 10) + (str[i++] - 48);
		else
			error_exit("Only positive numbers are allowed");
	}
	return (result);
}

void	to_parse(t_table *table, char **argv)
{
	int	i;

	i = 0;
	while (argv[i++])
	{
		table->philo_nbr = atol_check(argv[1]);
		table->time_to_die = atol_check(argv[2]);
		table->time_to_eat = atol_check(argv[3]);
		table->time_to_sleep = atol_check(argv[4]);
		if(argv[5])
			table->max_meals = atol_check(argv[5]);
	}
}