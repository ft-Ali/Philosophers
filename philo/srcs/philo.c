/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:22:40 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/18 11:23:20 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**

	* so 5 arguments are expected or 6 if you want to print the status of the philos
 * ./philo 5 800 200 200 [5]
 **/

const char	*valide_input(const char *str)
{
	const char	*nbr;

	nbr = validate_prefix(&str);
	if (nbr == NULL)
		return (NULL);
	return (validate_number(nbr));
}

const char	*validate_prefix(const char **str)
{
	while (is_space(**str))
		++(*str);
	if (**str == '+')
		++(*str);
	else if (**str == '-')
	{
		error_exit("Negative numbers are not allowed");
		return (NULL);
	}
	if (!is_digit(**str))
	{
		error_exit("Invalid input: not a digit");
		return (NULL);
	}
	return (*str);
}

const char	*validate_number(const char *str)
{
	int			len;
	const char	*nbr = str;

	len = 0;
	while (is_digit(*str))
	{
		++str;
		++len;
	}
	if (len > 10)
	{
		error_exit("Number is too big");
		return (NULL);
	}
	return (nbr);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		data.error_exit = 0;
		if (parse_input(&data, argv) != 0)
			return (1);
		if (init_data(&data) != 0)
		{
			free_data(&data);
			return (1);
		}
		if (routine_start(&data) != 0)
		{
			free_data(&data);
			return (1);
		}
		free_data(&data);
	}
	else
		error_exit("Invalid number of arguments\n"
			"Usage: ./philo [philo_nbr] [time_die] [time_eat] [time_sleep]");
	return (0);
}

/**
 * @brief Explication sur les threads et les mutex.
 *
 * Les threads sont des unités d'exécution légères qui permettent
 * à un programme de réaliser plusieurs tâches simultanément.
 * Ils partagent le même espace mémoire, ce qui facilite la
 * communication entre eux. Cependant, cela peut entraîner
 * des problèmes de concurrence lorsque plusieurs threads
 * tentent d'accéder ou de modifier des données partagées,
 * provoquant des comportements indésirables ou des erreurs
 *
 *
 * Les mutex (abréviation de "mutual exclusion") sont des
 * mécanismes de synchronisation qui contrôlent l'accès aux
 * ressources partagées. En verrouillant un mutex, un thread
 * obtient une exclusion mutuelle sur une section critique,
 * garantissant qu'un seul thread à la fois peut accéder
 * ou modifier une ressource donnée. Cela aide à prévenir
 * les conflits d'accès et assure l'intégrité des données.
 *
 * En résumé, l'utilisation de threads permet d'améliorer
 * la performance et la réactivité d'un programme, tandis
 * que les mutex assurent la sécurité et l'intégrité des
 * données dans un environnement multithreadé.
 */
