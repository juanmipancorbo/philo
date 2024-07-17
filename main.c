/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:45:27 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/17 20:07:08 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_exit(const char *error)
{
	printf(R"%s\n"RST, error);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		to_parse(&table, argv);
		to_init(&table);
		to_dinner(&table);
	}
	else
	{
		to_exit("WRONG INPUT\n"
			W"Try: \""G"./philo 4 900 300 300 "C"4"W"\"\n"
			W"      [nbr_philos] [t_die] [t_eat] [t_sleep]"C" [meals_limit]\n"
			C"					       Optional"RST);
	}
}
