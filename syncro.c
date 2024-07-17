/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:33:04 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/17 20:07:11 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_wait(t_table *table)
{
	while (!to_get(&table->table_mtx, &table->threads_ready))
		;
}
