/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:58:18 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/08 21:43:15 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	wait_threads(philo->table);//todo
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
}
