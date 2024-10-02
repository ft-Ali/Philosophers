/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:52:02 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/02 17:04:05 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_exit(char *msg)
{
	printf(RED "🚨 %s 🚨\n" RESET, msg);
	return (1);
}
void	free_data(t_data *data)
{
    if (data->philo)
        free(data->philo);
    if (data->forks)
        free(data->forks);
    // Ajoutez d'autres libérations de mémoire si nécessaire
}
