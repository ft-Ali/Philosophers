/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:34:33 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/10 15:32:25 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	think(t_philo *philo)
{
	write_status(THINK, philo, DEBUG);
}

static void	eat(t_philo *philo)
{
	protect_mutex_handle(&philo->right_fork->fork, LOCK);
	write_status(FORK_RIGHT, philo, DEBUG);
	protect_mutex_handle(&philo->left_fork->fork, LOCK);
	write_status(FORK_LEFT, philo, DEBUG);
	set_int(&philo->data->data_mtx, &philo->last_eat, gettime(MILLISECOND));
	philo->eat_count++;
	write_status(EAT, philo, DEBUG);
	ft_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->limit_eat > 0
		&& philo->eat_count == philo->data->limit_eat)
		set_bool(&philo->data->data_mtx, &philo->full, true);
	protect_mutex_handle(&philo->right_fork->fork, UNLOCK);
	protect_mutex_handle(&philo->left_fork->fork, UNLOCK);
}

void	*start_sim(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	wait_trhead(p->data);
	while (!simulation_end(p->data))
	{
		if (p->full)
			break ;
		eat(p);
		write_status(SLEEP, p, DEBUG);
		ft_usleep(p->data->time_to_sleep, p->data);
		think(p);
	}
	return (NULL);
}

void	*routine_start(t_data *data)
{
	int	i;

	i = -1;
	if (data->limit_eat == 0)
		return (NULL);
	else if (data->limit_eat == 1)
		return (NULL);
	else
	{
		while (++i < data->philo_nbr)
			protect_thread_handle(&data->philo[i].thread, start_sim,
				&data->philo[i], CREATE);
	}
	data->timestamp = gettime(MILLISECOND);
	set_bool(&data->data_mtx, &data->thread_ready, true);
	i = -1;
	while (++i < data->philo_nbr)
	{
		protect_thread_handle(&data->philo[i].thread, NULL, NULL, JOIN);
	}
	return (NULL);
}
