/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:45:27 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/04 07:11:33 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Arguments:
• number_of_philosophers: And forks.
• time_to_die: If one didn’t start eating time_to_die since the beginning
of their last meal or the beginning of the simulation, they die.
• time_to_eat: During that time, they will need to hold two forks.
• time_to_sleep: Time they spend sleeping.
• [number_of_times_each_philosopher_must_eat] (optional argument): If all 
philosophers have eaten at least this number of times, the simulation
stops. If not specified, the simulation stops when a philosopher dies.

About the logs of your program:
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork 
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
• A displayed state message should not be mixed up with another message.
• A message announcing a philosopher died should be displayed no more than 10
ms after the actual death of the philosopher.
• Again, philosophers should avoid dying!

The specific rules for the mandatory part are:
• Each philosopher should be a thread.
• There is one fork between each pair of philosophers. Therefore, if there 
are several philosophers, each philosopher has a fork on their left side and
a fork on their right side. If there is only one philosopher, there should 
be only one fork on the table.
• To prevent philosophers from duplicating forks, you should protect the 
forks state with a mutex for each of them.

Ex. entry values:

./philo 4 900 300 300 [4]
*/
#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		to_parse(&table, argv);
	}
	else
	{
		error_exit("WRONG INPUT\n"
			W"Try: \""G"./philo 4 900 300 300 "C"4"W"\"\n"
			W"      [nbr_philos] [t_die] [t_eat] [t_sleep]"C" [meals_limit]\n"
			C"					       Optional"RST);
	}
}
