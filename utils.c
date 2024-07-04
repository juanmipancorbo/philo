/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:09:16 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/04 07:11:35 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf(R"%s\n"RST, error);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if(!ret)
		error_exit("Malloc error.");
	return(ret);
}