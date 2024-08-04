/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:33:04 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/04 19:57:54 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	time_left;

	start = to_time(MICROSECOND, table);
	while (to_time(MICROSECOND, table) - start < usec)
	{
		if (to_finish(table))
			break ;
		elapsed = to_time(MICROSECOND, table) - start;
		time_left = usec - elapsed;
		if (time_left > 1e3)
			usleep(time_left / 2);
		else
			while (to_time(MICROSECOND, table) - start < usec)
				;
	}
}

int	to_wait(t_table *table)
{
	while (!to_get(&table->table_mtx, &table->threads_ready, table))
		;
	if (to_get(&table->table_mtx, &table->threads_ready, table == 1))
		return (0);
	else
		return (-1);
}

int	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr,
		t_table *table)
{
	int	ret;

	ret = 0;
	mutex_handler(mutex, LOCK, table);
	if (*threads == philo_nbr)
		ret = 1;
	mutex_handler(mutex, UNLOCK, table);
	return (ret);
}

int	to_increase(t_mtx *mutex, long *value, char *error, t_table *table)
{
	if (pthread_mutex_lock(mutex))
		return (to_exit("Mutex LOCK error."));
	(*value)++;
	if (pthread_mutex_unlock(mutex))
		return (to_exit("Mutex UNLOCK error."));
	else
		return (0);
}

void	to_detach(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			to_think(philo, 1);
	}
}
