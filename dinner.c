/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:58:18 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/10 20:53:30 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	to_think(t_philo *philo)
{
	print_status(THINKING, philo, DEBUG_MODE); 
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
	while (!to_finish(philo->table))
	{
		if (philo->full_of_food)
			break ;
		 
		to_eat(philo);
		print_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		to_think(philo);
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
		;
	else
		while (++i < table->philo_nbr)
			thread_handler(&table->philos[i].thread_id, to_start, 
							&table->philos[i], CREATE);
	table->start_time = to_time(MILLISECOND);
	to_set(&table->table_mtx, &table->threads_ready, 1);
	i = -1;
	while (++i < table->philo_nbr) 
		thread_handler(&table->philos[i].thread_id , NULL, NULL, JOIN);
}
