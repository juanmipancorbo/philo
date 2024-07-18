/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:41:39 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/18 21:31:54 by jpancorb         ###   ########.fr       */
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
	return (0);
}

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
	mutex_handler(&table->write_mtx, DESTROY);
	mutex_handler(&table->table_mtx, DESTROY);
	free (table->forks);
	free (table->philos);
}
