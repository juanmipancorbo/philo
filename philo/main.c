/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:45:27 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/28 14:34:06 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	to_exit(const char *error, t_table *table)
{
	printf(R"%s\n"RST, error);
	to_clean(table);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		to_parse(&table, argv);
		to_dinner(&table);
		to_clean(&table);
		printf(M"Dinner finished\n"RST);
	}
	else
	{
		to_exit("WRONG INPUT\n"
			W"Try: \"""./philo"Y" 4 "G"900 300 300 "C"4"W"\"\n"
			W"[Program] "Y"[nbr_philos] "G"[t_die] [t_eat] [t_sleep]"
			C" [meals_limit]\n"
			G"			  all in milliseconds"C"      Optional"RST,
			&table);
		return (1);
	}

	return (0);
}
