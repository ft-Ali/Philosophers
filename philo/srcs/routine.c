/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:34:33 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/18 13:20:47 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Permet à un philosophe de réfléchir pendant un temps donné.
 *
 * Si le paramètre presim est faux, le philosophe écrit son statut
 * dans le journal. Si le nombre de philosophes est pair, il sort
 * immédiatement sans penser. Sinon, il calcule le temps de réflexion
 * et dort un temps proportionnel à ce temps.
 *
 * @param philo Pointeur vers la structure du philosophe.
 * @param presim Indique si la simulation est en cours.
 */

void	think(t_philo *philo, bool presim)
{
	int	t_eat;
	int	t_sleep;
	int	t_think;

	if (!presim)
		write_status(THINK, philo, DEBUG);
	if (philo->data->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	t_think = t_eat * 2 + t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42, philo->data);
}

void	eat(t_philo *philo)
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

/**
 * @brief Démarre les threads de la simulation pour les philosophes.
 *
 * Crée les threads pour chaque philosophe et pour le moniteur.
 * Attend que tous les threads se terminent avant de sortir.
 *
 * @param data Pointeur vers les données de la simulation.
 * @return NULL
 */

int	create_threads(t_data *d)
{
	int	i;
	int	re;

	if (d->philo_nbr == 1)
	{
		re = t_handle(&d->philo[0].thread, solo_p, &d->philo[0], CREATE);
		if (re != 0)
			return (re);
	}
	else
	{
		i = -1;
		while (++i < d->philo_nbr)
		{
			re = t_handle(&d->philo[i].thread, start_sim, &d->philo[i], CREATE);
			if (re != 0)
				return (re);
		}
	}
	re = t_handle(&d->monitor, monitor, d, CREATE);
	if (re != 0)
		return (re);
	d->timestamp = gettime(MILLISECOND);
	set_bool(&d->data_mtx, &d->thread_ready, true);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;
	int	result;

	i = -1;
	while (++i < data->philo_nbr)
	{
		result = t_handle(&data->philo[i].thread, NULL, NULL,
				JOIN);
		if (result != 0)
			return (result);
	}
	set_bool(&data->data_mtx, &data->end_timestamp, true);
	result = t_handle(&data->monitor, NULL, NULL, JOIN);
	if (result != 0)
		return (result);
	return (0);
}

int	routine_start(t_data *data)
{
	int	result;

	if (data->philo_nbr <= 0)
		return (1);
	result = create_threads(data);
	if (result != 0)
		return (result);
	result = join_threads(data);
	if (result != 0)
		return (result);
	return (0);
}

// int	routine_start(t_data *data)
// {
// 	int	i;
// 	int	result;

// 	i = -1;
// 	if (data->philo_nbr <= 0)
// 		return (1);
// 	if (data->philo_nbr == 1)
// 	{
// 		result = protect_thread_handle(&data->philo[0].thread, solo_p,
// 				&data->philo[0], CREATE);
// 		if (result != 0)
// 			return (result);
// 	}
// 	else
// 	{
// 		while (++i < data->philo_nbr)
// 		{
// 			result = protect_thread_handle(&data->philo[i].thread, start_sim,
// 					&data->philo[i], CREATE);
// 			if (result != 0)
// 				return (result);
// 		}
// 	}
// 	// Lancer le thread de monitor
// 	result = protect_thread_handle(&data->monitor, monitor, data, CREATE);
// 	if (result != 0)
// 		return (result);
// 	data->timestamp = gettime(MILLISECOND);
// 	set_bool(&data->data_mtx, &data->thread_ready, true);
// 	i = -1;
// 	while (++i < data->philo_nbr)
// 	{
// 		result = protect_thread_handle(&data->philo[i].thread, NULL, NULL,
// 				JOIN);
// 		if (result != 0)
// 			return (result);
// 	}
// 	set_bool(&data->data_mtx, &data->end_timestamp, true);
// 	result = protect_thread_handle(&data->monitor, NULL, NULL, JOIN);
// 	if (result != 0)
// 		return (result);
// 	return (0);
// }
