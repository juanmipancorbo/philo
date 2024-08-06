/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:41:39 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/06 20:15:36 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (1);
}

void	to_clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->mtx);
		pthread_mutex_destroy(&table->forks[i].mtx);
	}
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->print_mtx);
	if (table->forks)
		free (table->forks);
	if (table->philos)
		free (table->philos);
}

void	to_set(t_mtx *mutex, long *dst, long value)
{
	pthread_mutex_lock(mutex);
	*dst = value;
	pthread_mutex_unlock(mutex);
}

long	to_get(t_mtx *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}
