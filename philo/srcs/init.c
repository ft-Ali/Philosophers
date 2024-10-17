/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:33:29 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/17 17:27:25 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	handle_fork(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	if (philo->id % 2 != 0)
	{
		philo->right_fork = &forks[(i + 1) % philo_nbr];
		philo->left_fork = &forks[i];
	}
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[i];
		philo->left_fork = &forks[(i + 1) % philo_nbr];
	}
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
		philo->last_eat = 0;
		protect_mutex_handle(&philo->philo_mtx, INIT);
		philo->eat_count = 0;
		philo->data = data;
		handle_fork(philo, data->forks, i);
	}
}

int	check_allocation(t_data *data)
{
	if (data->philo == NULL || data->forks == NULL)
	{
		if (data->philo != NULL)
			free(data->philo);
		if (data->forks != NULL)
			free(data->forks);
		protect_mutex_handle(&data->data_mtx, DESTROY);
		protect_mutex_handle(&data->print_mtx, DESTROY);
		error_exit("Memory allocation failed");
		return (1);
	}
	return (0);
}
/**
 * @brief Initialise les données du programme.
 *
 * Cette fonction initialise les structures et mutex nécessaires au
 * déroulement de la simulation. Elle alloue la mémoire pour les
 * philosophes et les fourchettes, puis initialise les mutex.
 *
 * @param data Pointeur vers la structure t_data contenant les
 * informations du programme.
 */

int	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->end_timestamp = false;
	data->thread_ready = false;
	data->thread_count = 0;
	protect_mutex_handle(&data->data_mtx, INIT);
	protect_mutex_handle(&data->print_mtx, INIT);
	data->philo = protect_malloc(sizeof(t_philo) * data->philo_nbr);
	data->forks = protect_malloc(sizeof(t_fork) * data->philo_nbr);
	if (check_allocation(data) != 0)
		return (1);
	while (++i < data->philo_nbr)
	{
		protect_mutex_handle(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	init_p(data);
	return (0);
}
