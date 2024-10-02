/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:33:29 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/02 16:53:59 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	handle_fork(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->right_fork = &forks[i];
	philo->left_fork = &forks[(i + 1) % philo_nbr];
}

static void	init_p(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->eat_count = 0;
		philo->data = data;
		handle_fork(philo, data->forks, i);
	}
}

void	init_data(t_data *data)
{
	int i;

	i = -1;
	data->end_timestamp = false;
	data->philo = protect_malloc(sizeof(t_philo) * data->philo_nbr);
	data->forks = protect_malloc(sizeof(t_fork) * data->philo_nbr);
	while (++i < data->philo_nbr)
	{
		protect_mutex_handle(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	init_p(data);
}