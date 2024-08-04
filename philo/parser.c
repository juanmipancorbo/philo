/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:14:12 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/04 20:14:10 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	atol_check(char *str, int type_arg)
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
			result = to_exit("Only positive numbers are allowed.", NULL);
	}
	if (result == 0)
		result = to_exit("Values cannot be 0.", NULL);
	if (type_arg == 0 && result > 1000)
		result = to_exit("The number of philos should not exceed 1000.", NULL);
	if (result > INT_MAX || i > 10)
		result = to_exit("Values cannot exceed INT_MAX.", NULL);
	if (type_arg == 1 && result < 60)
		result = to_exit("Values cannot be less than 60 ms.", NULL);
	return (result);
}

static void	to_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->table->philo_nbr == 1)
		philo->first_fork = &forks[0];
	else if (philo->id % 2)
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->second_fork = &forks[philo_position];
	}
	else
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static void	to_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full_of_food = 0;
		philo->meals_count = 0;
		philo->thread_id = 0;
		philo->table = table;
		if (pthread_mutex_init(&philo->mtx, NULL))
			return (to_exit("Mutex INIT error (philo[%d].mtx).", i + 1));
		to_forks(philo, table->forks, i);
	}
}

static int	to_init(t_table *table)
{
	int	i;

	i = -1;
	// table->end = 0;
	// table->threads_ready = 0;
	// table->nbr_threads_running = 0;
	// table->monitor = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (to_exit("Malloc error."));
	table->forks = to_malloc(sizeof(t_fork) * table->philo_nbr, table);
	if (!table->forks)
		return (to_exit("Malloc error."));
	if (pthread_mutex_init(&table->table_mtx, NULL))
		return (to_exit("Mutex INIT error (table_mtx)."));
	if (pthread_mutex_init(&table->print_mtx, NULL))
		return (to_exit("Mutex INIT error (print_mtx)."));
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].mtx, NULL))
			return (to_exit("Mutex INIT error (forks[%d].mtx).", i));
		table->forks[i].id = i;
	}
	to_philos(table);
}

int	to_parse(t_table *table, char **argv)
{
	table->philo_nbr = atol_check(argv[1], 0);
	if (table->philo_nbr < 0)
		return (1);
	table->time_to_die = atol_check(argv[2], 1) * 1e3;
	if (table->time_to_die < 0)
		return (1);
	table->time_to_eat = atol_check(argv[3], 1) * 1e3;
	if (table->time_to_eat < 0)
		return (1);
	table->time_to_sleep = atol_check(argv[4], 1) * 1e3;
	if (table->time_to_sleep < 0)
		return (1);
	if (argv[5])
	{
		table->max_meals = atol_check(argv[5], 2);
		if (table->max_meals < 0)
			return (1);
	}
	if (to_init(table))
		return (1);
	return (0);
}
