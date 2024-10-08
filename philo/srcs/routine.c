/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:34:33 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/08 17:11:23 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*start_sim(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	wait_trhead(philo->data);
	return (NULL);
}

void	*routine_start(t_data *data)
{
	int i;

	i = -1;
	if (data->limit_eat == 0)
		return ;
	else if (data->limit_eat == 1)
		// a faire
	else
		{
			while (++i < data->philo_nbr)
				protect_thread_handle(&data->philo[i].thread, start_sim,
					&data->philo[i], CREATE);
		}
	
}