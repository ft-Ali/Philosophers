/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:22:40 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/01 14:49:35 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
	// t_philo *philo;
	(void)argv;
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	// philo = init_philo(argc, argv);
	printf("test\n");
	// if (!philo)
	// 	return (1);
	// if (start_simulation(philo))
	// 	return (1);
	return (0);
}