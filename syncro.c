/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:33:04 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/18 21:20:07 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_wait(t_table *table)
{
	while (!to_get(&table->table_mtx, &table->threads_ready))
		;
}

int	no_dead(t_mtx *mutex, long *threads, long philo_nbr)
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
