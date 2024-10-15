/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:22:40 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/15 11:18:44 by alsiavos         ###   ########.fr       */
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
		data.error_exit = 0;

		// Si la fonction parse_input retourne une erreur, on arrête le programme.
		if (parse_input(&data, argv) != 0)
			return (1);

		// Si pas d'erreur, on continue
		init_data(&data);
		routine_start(&data);
		free_data(&data);  // Libère la mémoire après la simulation
	}
	else
	{
		error_exit("Invalid number of arguments\n"
					"Usage: ./philo [philo_nbr] [time_to_die] [time_to_eat] [time_to_sleep]");
		return (1);
	}

	return (0);  // Retourne 0 si tout s'est bien passé
}