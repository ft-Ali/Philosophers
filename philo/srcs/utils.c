/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:52:02 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/08 14:27:08 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_fork(t_philo *philo, int philo_nbr)
{
	int	i;

	i = 0;
	while (i < philo_nbr)
	{
		printf("Philosopher %d has %d forks\n", i, philo[i].left_fork->fork_id);
		printf("\n");
		printf("Philosopher %d has %d forks\n", i, philo[i].right_fork->fork_id);
		i++;
	}
}

int	error_exit(char *msg)
{
	printf(RED "🚨 %s 🚨\n" RESET, msg);
	return (0);
}
void	free_data(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	// Ajoutez d'autres libérations de mémoire si nécessaire
}
