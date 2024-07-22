/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:45:27 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/22 18:55:45 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		to_parse(&table, argv);
		to_init(&table);
		to_dinner(&table);
		to_clean(&table);
		printf(M"Dining finished\n"RST);
	}
	else
	{
		to_exit("WRONG INPUT\n"
			W"Try: \""G"./philo 4 900 300 300 "C"4"W"\"\n"
			W"      [nbr_philos] [t_die] [t_eat] [t_sleep]"C" [meals_limit]\n"
			C"					       Optional"RST);
	}
	return (0);
}
