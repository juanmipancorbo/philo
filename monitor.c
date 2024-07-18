/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:29:02 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/18 21:30:57 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	to_die(t_philo *philo)
{
	long	elapsed;

	if (to_get(&philo->mtx, &philo->full_of_food))
		return (0);
	elapsed = to_time(MILLISECOND) - to_get(&philo->mtx,
			&philo->last_meal_time);
	if (elapsed > (philo->table->time_to_die / 1e3))
		return (1);
	return (0);
}

void	*to_monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!no_dead(&table->table_mtx, &table->nbr_threads_running,
			table->philo_nbr))
		;
	while (!to_finish(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !to_finish(table))
		{
			if (to_die(table->philos + i))
			{
				to_set(&table->table_mtx, &table->end_simulation, 1);
				print_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
