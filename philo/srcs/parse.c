/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:51:51 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/17 16:21:29 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

long	ft_atol(const char *str)
{
	long	res;
	long	limit;

	res = 0;
	limit = (long)INT_MAX;
	str = valide_input(str);
	if (!str)
		return (-1);
	while (is_digit(*str))
	{
		res = res * 10 + (*str - '0');
		if (res > limit)
		{
			error_exit("Number exceeds INT_MAX");
			return (-1);
		}
		++str;
	}
	if (*str != '\0')
	{
		error_exit("Invalid input: contains non-digit characters");
		return (-1);
	}
	return (res);
}
/**
 * @brief Valide et convertit les arguments d'entrée.
 *
 * Analyse les arguments fournis par l'utilisateur pour initialiser
 * les paramètres du programme. Vérifie que le nombre de philosophes
 * est valide et que les temps sont corrects.
 *
 * @param data Structure stockant les paramètres du programme.
 * @param argv Tableau contenant les arguments d'entrée.
 *
 * @return 0 si tout est correct, 1 en cas d'erreur.
 */

int	parse_input(t_data *data, char **argv)
{
	data->philo_nbr = ft_atol(argv[1]);
	if (data->philo_nbr <= 0 || data->philo_nbr > 200)
		return (error_exit("Number of philosophers must be between 1 and 200"));
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (error_exit("Invalid input values"));
	if (data->time_to_die < 60000 || data->time_to_eat < 60000
		|| data->time_to_sleep < 60000)
		return (error_exit("Use timestamps more than 60ms"));
	if (argv[5])
		data->limit_eat = ft_atol(argv[5]);
	else
		data->limit_eat = -1;
	return (0);
}
