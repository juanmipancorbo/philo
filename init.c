/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:14:12 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/04 07:11:31 by jpancorb         ###   ########.fr       */
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
			error_exit("Only positive numbers are allowed.");
	}
	if (result > INT_MAX || i > 10)
		error_exit("Values cannot exceed INT_MAX.");
	if (result < 60)
		error_exit("Values cannot be less than 60 ms.");
	return (result);
}

void	to_parse(t_table *table, char **argv)
{
	int	i;

	i = 0;
	while (argv[i++])
	{
		table->philo_nbr = atol_check(argv[1]) * 1e3;
		table->time_to_die = atol_check(argv[2]) * 1e3;
		table->time_to_eat = atol_check(argv[3]) * 1e3;
		table->time_to_sleep = atol_check(argv[4]) * 1e3;
		if(argv[5])
			table->max_meals = atol_check(argv[5]);
	}
}

void	to_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while(i++ < table->philo_nbr)
	{
		if(pthread_mutex_init(&table->forks[i].fork, NULL))
			error_exit("Problem initializing the mutex.");
		table->forks[i].fork_id = i;
	}
} 