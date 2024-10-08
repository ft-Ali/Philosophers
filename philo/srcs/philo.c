/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:22:40 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/08 14:15:43 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**

	* so 5 arguments are expected or 6 if you want to print the status of the philos
 * ./philo 5 800 200 200 [5]
 **/

int	main(int argc, char **argv)
{
	t_data data;
	
	
	if (argc == 5 || argc == 6)
	{
		parse_input(&data, argv);
		// init data && create philos
		init_data(&data);
		// start simulation
		// start_simulation(&data);
		// free data after simulation = philo full or philo has died
		check_fork(data.philo, data.philo_nbr);
		free_data(&data);
	}
	else
		error_exit("Invalid number of arguments\n"
					"Usage: ./philo [philo_nbr] [time_to_die] [time_to_eat] [time_to_sleep]");

	return (0);
}