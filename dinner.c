/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:58:18 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/22 18:58:21 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_think(t_philo *philo, int to_detach)
{
	long	t_think;

	if (!to_detach)
		print_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_think = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	*to_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	to_wait(philo->table);
	to_set(&philo->mtx, &philo->last_meal_time, to_time(MILLISECOND));
	to_increase(&philo->table->table_mtx, &philo->table->nbr_threads_running);
	print_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!to_finish(philo->table))
		usleep(200);
	return (NULL);
}

void	to_eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->mtx, LOCK);
	print_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	mutex_handler(&philo->second_fork->mtx, LOCK);
	print_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	to_set(&philo->mtx, &philo->last_meal_time, to_time(MILLISECOND));
	philo->meals_count++;
	print_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->max_meals > 0
		&& philo->meals_count == philo->table->max_meals)
		to_set(&philo->mtx, &philo->full_of_food, 1);
	mutex_handler(&philo->first_fork->mtx, UNLOCK);
	mutex_handler(&philo->second_fork->mtx, UNLOCK);
}

void	*to_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	to_wait(philo->table);
	to_set(&philo->mtx, &philo->last_meal_time, to_time(MILLISECOND));
	to_increase(&philo->table->table_mtx, &philo->table->nbr_threads_running);
	to_detach(philo);
	while (!to_finish(philo->table))
	{
		if (philo->full_of_food)
			break ;
		to_eat(philo);
		print_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		to_think(philo, 0);
	}
	return (NULL);
}

void	to_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->max_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		thread_handler(&table->philos[0].thread_id, to_alone, &table->philos[0],
			CREATE);
	else
		while (++i < table->philo_nbr)
			thread_handler(&table->philos[i].thread_id, to_start,
				&table->philos[i], CREATE);
	thread_handler(&table->monitor, to_monitor, table, CREATE);
	table->start_time = to_time(MILLISECOND);
	to_set(&table->table_mtx, &table->threads_ready, 1);
	i = -1;
	while (++i < table->philo_nbr)
		thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	to_set(&table->table_mtx, &table->end_time, 1);
	thread_handler(&table->monitor, NULL, NULL, JOIN);
}
