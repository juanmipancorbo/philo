/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:33:04 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/25 19:31:12 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	time_left;

	start = to_time(MICROSECOND);
	while (to_time(MICROSECOND) - start < usec)
	{
		if (to_finish(table))
			break ;
		elapsed = to_time(MICROSECOND) - start;
		time_left = usec - elapsed;
		if (time_left > 1e3)
			usleep(time_left / 2);
		else
			while (to_time(MICROSECOND) - start < usec)
				;
	}
}

void	to_wait(t_table *table)
{
	while (!to_get(&table->table_mtx, &table->threads_ready))
		;
}

int	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	int	ret;

	ret = 0;
	mutex_handler(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = 1;
	mutex_handler(mutex, UNLOCK);
	return (ret);
}

void	to_increase(t_mtx *mutex, long *value)
{
	mutex_handler(mutex, LOCK);
	(*value)++;
	mutex_handler(mutex, UNLOCK);
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
