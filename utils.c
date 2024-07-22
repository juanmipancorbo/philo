/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:41:39 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/22 19:20:33 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*to_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		to_exit("Malloc error.");
	return (ret);
}

long	to_time(t_time_code time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		to_exit("Gettimeofday failed.");
	else if (SECOND == time_code)
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((time.tv_sec * 1e6) + time.tv_usec);
	else
		to_exit("Wrong input to \'to_time\'.");
	return (0);
}

void	to_clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		mutex_handler(&philo->mtx, DESTROY);
	}
	mutex_handler(&table->print_mtx, DESTROY);
	mutex_handler(&table->table_mtx, DESTROY);
	free (table->forks);
	free (table->philos);
}

void	to_set(t_mtx *mutex, long *dst, long value)
{
	mutex_handler(mutex, LOCK);
	*dst = value;
	mutex_handler(mutex, UNLOCK);
}

long	to_get(t_mtx *mutex, long *value)
{
	long	ret;

	mutex_handler(mutex, LOCK);
	ret = *value;
	mutex_handler(mutex, UNLOCK);
	return (ret);
}
