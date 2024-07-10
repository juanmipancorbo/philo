/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:40:39 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/10 19:41:03 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int		to_finish(t_table *table)
{
	return (to_get(&table->table_mtx, &table->end_simulation));
}