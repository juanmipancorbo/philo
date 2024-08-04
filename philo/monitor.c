/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:29:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/04 20:20:34 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	to_finish(t_table *table)
{
	return (to_get(&table->table_mtx, &table->end, table));
}

static void	print_status_debug(t_status status, t_philo *philo, long elapsed,
	t_table *table)
{
	if (!to_finish(philo->table))
	{
		if (TAKE_FIRST_FORK == status)
			printf(W "%-6ld" RST" %d has taken the first fork [%d]\n",
				elapsed, philo->id, philo->first_fork->id);
		else if (TAKE_SECOND_FORK == status)
			printf(W "%-6ld" RST" %d has taken the second fork [%d]\n",
				elapsed, philo->id, philo->second_fork->id);
		else if (EATING == status)
			printf(W "%-6ld"C" %d is eating [%ld meals eaten]\n" RST,
				elapsed, philo->id, philo->meals_count);
		else if (SLEEPING == status)
			printf(W "%-6ld" RST" %d is sleeping\n" RST, elapsed, philo->id);
		else if (THINKING == status)
			printf(W "%-6ld" RST" %d is thinking\n" RST, elapsed, philo->id);
	}
	else if (DIED == status)
		printf(R "%-6ld"C" %d died\n" RST, elapsed, philo->id);
	mutex_handler(&philo->table->table_mtx, UNLOCK, table);
}

void	print_status(t_status status, t_philo *philo, int debug, t_table *table)
{
	long	elapsed;

	elapsed = to_time(MILLISECOND, table) - philo->table->start_time;
	if (philo->full_of_food)
		return ;
	mutex_handler(&philo->table->print_mtx, LOCK, table);
	if (debug)
		print_status_debug(status, philo, elapsed, table);
	else if (!to_finish(philo->table))
	{
		if (TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			printf(W "%-6ld" RST" %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status)
			printf(W "%-6ld"C" %d is eating\n" RST, elapsed, philo->id);
		else if (SLEEPING == status)
			printf(W "%-6ld" RST" %d is sleeping\n" RST, elapsed, philo->id);
		else if (THINKING == status)
			printf(W "%-6ld" RST" %d is thinking\n" RST, elapsed, philo->id);
	}
	else if (DIED == status)
		printf(R "%-6ld"C" %d died\n" RST, elapsed, philo->id);
	mutex_handler(&philo->table->print_mtx, UNLOCK, table);
}

static int	to_die(t_philo *philo)
{
	long	elapsed;

	if (to_get(&philo->mtx, &philo->full_of_food, philo->table))
		return (0);
	elapsed = to_time(MILLISECOND, philo->table) - to_get(&philo->mtx,
			&philo->last_meal_time, philo->table);
	if (elapsed > (philo->table->time_to_die / 1e3))
		return (1);
	return (0);
}

void	*to_monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mtx, &table->nbr_threads_running,
			table->philo_nbr, table))
		;
	while (!to_finish(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !to_finish(table))
		{
			if (to_die(table->philos + i))
			{
				to_set(&table->table_mtx, &table->end, 1, table);
				print_status(DIED, table->philos + i, DEBUG_MODE, table);
			}
		}
	}
	return (NULL);
}
