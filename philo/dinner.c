/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:58:18 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/06 20:24:40 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_think(t_philo *philo, int to_detach)
{
	long	t_think;

	if (!to_detach)
		print_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_think = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

static void	*to_alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	to_wait(philo->table);
	to_set(&philo->mtx, &philo->last_meal_time, to_time(MILLISECOND));
	to_increase(&philo->table->table_mtx, &philo->table->nbr_threads_running);
	print_status(TAKE_FIRST_FORK, philo);
	while (!to_finish(philo->table))
		usleep(200);
	return (NULL);
}

static void	to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->mtx);
	print_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->mtx);
	print_status(TAKE_SECOND_FORK, philo);
	to_set(&philo->mtx, &philo->last_meal_time, to_time(MILLISECOND));
	philo->meals_count++;
	print_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->max_meals > 0
		&& philo->meals_count == philo->table->max_meals)
		to_set(&philo->mtx, &philo->full_of_food, 1);
	pthread_mutex_unlock(&philo->first_fork->mtx);
	pthread_mutex_unlock(&philo->second_fork->mtx);
}

static void	*to_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	to_wait(philo->table);
	to_set(&philo->mtx, &philo->last_meal_time,
		to_time(MILLISECOND));
	to_increase(&philo->table->table_mtx,
		&philo->table->nbr_threads_running);
	to_detach(philo);
	while (!to_finish(philo->table))
	{
		if (philo->full_of_food)
			break ;
		to_eat(philo);
		print_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		to_think(philo, 0);
	}
	return (NULL);
}

int	to_dinner(t_table *table)
{
	int		i;

	i = -1;
	if (table->philo_nbr == 1)
		if (pthread_create(&table->philos[0].thread_id, NULL, to_alone,
				&table->philos[0]))
			return (to_exit("Thread CREATE error (philo alone)."));
	if (table->philo_nbr > 1)
		while (++i < table->philo_nbr)
			if (pthread_create(&table->philos[i].thread_id, NULL, to_start,
					&table->philos[i]))
				return (to_exit("Thread CREATE error (philos thread)."));
	if (pthread_create(&table->monitor, NULL, to_monitor, table))
		return (to_exit("Thread CREATE error (table->monitor)."));
	table->start_time = to_time(MILLISECOND);
	to_set(&table->table_mtx, &table->threads_ready, 1);
	i = -1;
	while (++i < table->philo_nbr)
		if (pthread_join(table->philos[i].thread_id, NULL))
			return (to_exit("Thread JOIN error."));
	to_set(&table->table_mtx, &table->end, 1);
	if (pthread_join(table->monitor, NULL))
		return (to_exit("Thread JOIN error (table->monitor)."));
	return (0);
}
