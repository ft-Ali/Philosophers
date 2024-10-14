/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:51:51 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/14 15:33:41 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

const char	*valide_input(const char *str)
{
	int			len;
	const char	*nbr;
	t_data		data;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
	{
		data.error_exit = 1;
	}
	if (!is_digit(*str))
	{
		data.error_exit = 1;
	}
	nbr = str;
	while (is_digit(*str))
	{
		++str;
		++len;
	}
	if (len > 10)
		error_exit("Number is too big");
	if (*str != '\0')
		error_exit("Invalid input");
	return (nbr);
}

static long	ft_atol(const char *str)
{
	long	res;
	t_data 		data;

	res = 0;
	str = valide_input(str);
	while (is_digit(*str))
	{
		res = res * 10 + (*str - '0');
		++str;
	}
	if (res > INT_MAX)
	{
		data.error_exit = 1;
		
	}
	return (res);
}

void	parse_input(t_data *data, char **argv)
{
	data->philo_nbr = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (data->time_to_die < 6e4 || data->time_to_eat < 6e4
		|| data->time_to_sleep < 6e4)
		error_exit("Use timestamps more than 60ms");
	if (argv[5])
		data->limit_eat = ft_atol(argv[5]);
	else
		data->limit_eat = -1;
}
