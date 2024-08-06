/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:45:27 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/06 21:08:47 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	to_exit(const char *error)
{
	printf(R "%s\n" RST, error);
	return (-1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (to_parse(&table, argv))
			return (1);
		if (to_dinner(&table))
			return (1);
		printf(M"Dinner finished\n"RST);
		to_clean(&table);
		return (0);
	}
	else
	{
		to_exit("WRONG INPUT\n"
			W"Try: \"""./philo"Y" 4 "G"900 300 300 "C"4"W"\"\n"
			W"[Program] "Y"[nbr_philos] "G"[t_die] [t_eat] [t_sleep]"
			C" [meals_limit]\n"
			G"			  all in milliseconds"C"      Optional"RST);
		return (1);
	}
}
