/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:58:18 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/04 15:23:47 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_think(t_philo *philo, int to_detach)
{
	long	t_think;

	if (!to_detach)
		print_status(THINKING, philo, DEBUG_MODE, philo->table);
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
	to_set(&philo->mtx, &philo->last_meal_time,
		to_time(MILLISECOND, philo->table), philo->table);
	to_increase(&philo->table->table_mtx, &philo->table->nbr_threads_running,
		philo->table);
	print_status(TAKE_FIRST_FORK, philo, DEBUG_MODE, philo->table);
	while (!to_finish(philo->table))
		usleep(200);
	return (NULL);
}

static void	to_eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->mtx, LOCK, philo->table);
	print_status(TAKE_FIRST_FORK, philo, DEBUG_MODE, philo->table);
	mutex_handler(&philo->second_fork->mtx, LOCK, philo->table);
	print_status(TAKE_SECOND_FORK, philo, DEBUG_MODE, philo->table);
	to_set(&philo->mtx, &philo->last_meal_time,
		to_time(MILLISECOND, philo->table), philo->table);
	philo->meals_count++;
	print_status(EATING, philo, DEBUG_MODE, philo->table);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->max_meals > 0
		&& philo->meals_count == philo->table->max_meals)
		to_set(&philo->mtx, &philo->full_of_food, 1, philo->table);
	mutex_handler(&philo->first_fork->mtx, UNLOCK, philo->table);
	mutex_handler(&philo->second_fork->mtx, UNLOCK, philo->table);
}

static void	*to_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	to_wait(philo->table);
	to_set(&philo->mtx, &philo->last_meal_time,
		to_time(MILLISECOND, philo->table), philo->table);
	to_increase(&philo->table->table_mtx, &philo->table->nbr_threads_running,
		philo->table);
	to_detach(philo);
	while (!to_finish(philo->table))
	{
		if (philo->full_of_food)
			break ;
		to_eat(philo);
		print_status(SLEEPING, philo, DEBUG_MODE, philo->table);
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
		if (pthread_create(&table->philos[0], NULL, to_alone,
				&table->philos[0]))
			to_error("Thread CREATE error (philo[0]).");
	if (table->philo_nbr > 1)
		while (++i < table->philo_nbr)
			if (thread_create(&table->philos[i].thread_id, NULL, to_start,
					&table->philos[i]))
				to_error("Thread CREATE error (philos[%d].thread_id).", i);
	if (thread_create(&table->monitor, NULL, to_monitor, table))
		to_error("Thread CREATE error (table->monitor).");
	table->start_time = to_time(MILLISECOND, table);
	to_set(&table->table_mtx, &table->threads_ready, 1, table);
	i = -1;
	while (++i < table->philo_nbr && !err)
		if (thread_join(&table->philos[i].thread_id, NULL))
			to_error("Thread JOIN error (philos[%d].thread_id).", i);
	to_set(&table->table_mtx, &table->end_time, 1, table);
	if (thread_join(&table->monitor, NULL))
		to_error("Thread JOIN error (table->monitor).");
	thread_handler(&table->monitor, NULL, NULL, JOIN);
}
