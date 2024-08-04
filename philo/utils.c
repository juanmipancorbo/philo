/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:41:39 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/04 20:41:58 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	to_time(t_time_code time_code, t_table *table)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		to_exit("Gettimeofday failed.", table);
	else if (SECOND == time_code)
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((time.tv_sec * 1e6) + time.tv_usec);
	else
		to_exit("Wrong input to \'to_time\'.", table);
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
		mutex_handler(&philo->mtx, DESTROY, table);
		mutex_handler(&table->forks[i].mtx, DESTROY, table);
	}
	mutex_handler(&table->table_mtx, DESTROY, table);
	mutex_handler(&table->print_mtx, DESTROY, table);
	free (table->forks);
	free (table->philos);
}

int	to_set(t_mtx *mutex, long *dst, long value, t_table *table)
{
	if (pthread_mutex_lock(mutex))
		return (to_exit("Mutex LOCK error."));
	*dst = value;
	if (pthread_mutex_unlock(mutex))
		return (to_exit("Mutex UNLOCK error."));
	else
		return (0);
}

long	to_get(t_mtx *mutex, long *value, t_table *table)
{
	long	ret;

	if (pthread_mutex_lock(mutex))
		return (to_exit("Mutex LOCK error."));
	ret = *value;
	if (pthread_mutex_unlock(mutex))
		return (to_exit("Mutex UNLOCK error."));
	return (ret);
}
