/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:41:53 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/17 21:47:47 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status_debug(t_status status, t_philo *philo, long elapsed)
{
	if (!to_finish(philo->table))
	{
		if (TAKE_FIRST_FORK == status)
			printf(W"%-6ld"RST" %d has taken the first fork [%d]\n",
				elapsed, philo->id, philo->first_fork->id);
		else if (TAKE_SECOND_FORK == status)
			printf(W"%-6ld"RST" %d has taken the second fork [%d]\n",
				elapsed, philo->id, philo->second_fork->id);
		else if (EATING == status)
			printf(W"%-6ld"C" %d is eating [%ld meals eaten]\n"RST,
				elapsed, philo->id, philo->meals_count);
		else if (SLEEPING == status)
			printf(W"%-6ld"RST" %d is sleeping\n"RST, elapsed, philo->id);
		else if (THINKING == status)
			printf(W"%-6ld"RST" %d is thinking\n"RST, elapsed, philo->id);
	}
	else if (DIED == status)
		printf(R"%-6ld"C" %d died\n"RST, elapsed, philo->id);
	mutex_handler(&philo->table->table_mtx, UNLOCK);
}

void	print_status(t_status status, t_philo *philo, int debug)
{
	long	elapsed;

	elapsed = to_time(MILLISECOND) - philo->table->start_time;
	if (philo->full_of_food)
		return ;
	mutex_handler(&philo->table->write_mtx, LOCK);
	if (debug)
		print_status_debug(status, philo, elapsed);
	else if (!to_finish(philo->table))
	{
		if (TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status)
			printf(W"%-6ld"C" %d is eating\n"RST, elapsed, philo->id);
		else if (SLEEPING == status)
			printf(W"%-6ld"RST" %d is sleeping\n"RST, elapsed, philo->id);
		else if (THINKING == status)
			printf(W"%-6ld"RST" %d is thinking\n"RST, elapsed, philo->id);
	}
	else if (DIED == status)
		printf(R"%-6ld"C" %d died\n"RST, elapsed, philo->id);
	mutex_handler(&philo->table->write_mtx, UNLOCK);
}
