/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:14:12 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/07 19:37:03 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	atol_check(char *str, int argv_1)
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
			to_exit("Only positive numbers are allowed.");
	}
	if (result == 0)
		to_exit("Values cannot be 0.");
	if (result > INT_MAX || i > 10)
		to_exit("Values cannot exceed INT_MAX.");
	if (!argv_1 && result < 60)
		to_exit("Values cannot be less than 60 ms.");
	return (result);
}

void	to_parse(t_table *table, char **argv)
{
	int	i;

	i = 0;
	while (argv[i++])
	{
		table->philo_nbr = atol_check(argv[1], 1) * 1e3;
		table->time_to_die = atol_check(argv[2], 0) * 1e3;
		table->time_to_eat = atol_check(argv[3], 0) * 1e3;
		table->time_to_sleep = atol_check(argv[4], 0) * 1e3;
		if(argv[5])
			table->max_meals = atol_check(argv[5], 0);
	}
}

static void	to_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if(philo->id % 2)
	{
		philo->left_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->right_fork = &forks[philo_position];
	}
	else
	{	
		philo->right_fork = &forks[philo_position];
		philo->left_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static void	to_philos(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while(++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full_of_food = 0;
		philo->meals_count = 0;
		philo->table = table;
		to_forks(philo, table->forks, i);
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
		mutex_handler(&table->forks[i].mtx, INIT);
		table->forks[i].id = i; 
	}
	to_philos(table);
}