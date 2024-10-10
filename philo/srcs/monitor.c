/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:16:39 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/10 23:16:39 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool philo_died(t_philo *philo)
{
	int time;
	int t_die;


	if(get_bool(&philo->data->data_mtx, &philo->full))
		return (false);
	time = gettime(MILLISECOND) - get_int(&philo->data->data_mtx, &philo->last_eat);
	t_die = philo->data->time_to_die / 1000;

	if(time > t_die)
		return (true);
	return (false);
}

void *monitor(void *data)
{
	t_data *d;
	int i;

	d = (t_data *)data;
	while(!all_threads_ready(&d->data_mtx, &d->thread_count, d->philo_nbr))
		;
	while(!simulation_end(d))
	{
		i = -1;
		while(++i < d->philo_nbr && !simulation_end(d))
		{
			if(philo_died(d->philo + i))
			{
				set_bool(&d->data_mtx, &d->end_timestamp, true);
				write_status(DIED, d->philo + i, DEBUG);
			}
		}
	}

	return (NULL);
}