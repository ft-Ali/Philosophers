/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:49:45 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/17 17:32:15 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Attend que tous les threads soient prêts.
 *
 * Cette fonction bloque l'exécution jusqu'à ce que tous les threads
 * aient signalé qu'ils sont prêts. Elle utilise une vérification
 * sur un mutex pour s'assurer que l'état des threads est correctement
 * lu sans conflit.
 *
 * @param data Pointeur vers la structure de données contenant l'état
 *              des threads.
 */

void	wait_trhead(t_data *data)
{
	while (!get_bool(&data->data_mtx, &data->thread_ready))
		;
}

void	increase_int(t_mtx *mtx, int *dest)
{
	protect_mutex_handle(mtx, LOCK);
	(*dest)++;
	protect_mutex_handle(mtx, UNLOCK);
}

/**
 * @brief Vérifie si tous les threads sont prêts.
 *
 * Cette fonction détermine si le nombre de threads prêts
 * est égal au nombre total de philosophes. Elle utilise un mutex
 * pour garantir l'accès sécurisé aux données partagées.
 *
 * @param mtx Pointeur vers le mutex pour synchroniser l'accès.
 * @param threads Pointeur vers le compteur de threads prêts.
 * @param philo_nbr Nombre total de philosophes.
 * @return true si tous les threads sont prêts, sinon false.
 */

bool	all_threads_ready(t_mtx *mtx, int *threads, int philo_nbr)
{
	bool	ready;

	ready = false;
	protect_mutex_handle(mtx, LOCK);
	if (*threads == philo_nbr)
		ready = true;
	protect_mutex_handle(mtx, UNLOCK);
	return (ready);
}

void	write_status_debug(t_estatus status, t_philo *philo, int elapsed)
{
	if (FORK_RIGHT == status && !simulation_end(philo->data))
		printf(GREY "%d ms" RESET " %d has taken r_f (Fork ID: %d)🍴 \n",
			elapsed, philo->id, philo->right_fork->fork_id);
	else if (FORK_LEFT == status && !simulation_end(philo->data))
		printf(GREY "%d ms" RESET " %d has taken the L_F 🍴 (Fork ID:%d)\n",
			elapsed, philo->id, philo->left_fork->fork_id);
	else if (EAT == status && !simulation_end(philo->data))
		printf(GREEN "%d ms  %d is eating 🍽️ (Meals: %d)\n" RESET, elapsed,
			philo->id, philo->eat_count);
	else if (SLEEP == status && !simulation_end(philo->data))
		printf(CYAN "%d " RESET " %d is sleeping 💤\n", elapsed, philo->id);
	else if (THINK == status && !simulation_end(philo->data))
		printf(YELLOW "%d " RESET " %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status && simulation_end(philo->data))
	{
		printf("💀 %d died in %d ms 💀\n", philo->id, elapsed);
		error_exit("A philosopher died");
	}
}

void	write_status(t_estatus status, t_philo *philo, bool debug)
{
	int	elapsed;

	elapsed = gettime(MILLISECOND) - philo->data->timestamp;
	if (philo->full)
		return ;
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		protect_mutex_handle(&philo->data->print_mtx, LOCK);
		if ((status == FORK_RIGHT || status == FORK_LEFT)
			&& !simulation_end(philo->data))
			printf(GREY "%d ms" RESET " %d has taken a fork\n", elapsed,
				philo->id);
		else if (status == EAT && !simulation_end(philo->data))
			printf(GREEN "%d ms" RESET " %d is eating\n", elapsed, philo->id);
		else if (status == SLEEP && !simulation_end(philo->data))
			printf(CYAN "%d ms" RESET " %d is sleeping\n", elapsed, philo->id);
		else if (status == THINK && !simulation_end(philo->data))
			printf(YELLOW "%d ms" RESET " %d is thinking\n", elapsed,
				philo->id);
		else if (status == DIED && simulation_end(philo->data))
			printf(RED "💀 %d died in %d ms 💀\n" RESET, philo->id, elapsed);
		protect_mutex_handle(&philo->data->print_mtx, UNLOCK);
	}
}
