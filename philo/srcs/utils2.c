/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:49:45 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/09 17:36:11 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_trhead(t_data *data)
{
	while (!get_bool(&data->data_mtx, &data->thread_ready))
		;
}

static void write_status_debug(t_estatus status, t_philo *philo, int elapsed)
{
    if (FORK_RIGHT == status && !simulation_end(philo->data))
        printf(GREY "%-6ld" RESET "%d has taken the right fork 🍴 (Fork ID: %d)\n", elapsed, philo->id, philo->right_fork->fork_id);
    else if (FORK_LEFT == status && !simulation_end(philo->data))
        printf(GREY "%-6ld" RESET "%d has taken the left fork 🍴 (Fork ID: %d)\n", elapsed, philo->id, philo->left_fork->fork_id);
    else if (EAT == status && !simulation_end(philo->data))
        printf(GREEN "%-6ld" RESET "%d is eating 🍽️ (Meals: %d)\n", elapsed, philo->id, philo->);
    else if (SLEEP == status && !simulation_end(philo->data))
        printf(CYAN "%-6ld" RESET "%d is sleeping 💤\n", elapsed, philo->id);
    else if (THINK == status && !simulation_end(philo->data))
        printf(YELLOW "%-6ld" RESET "%d is thinking 🤔\n", elapsed, philo->id);
    else if (DIED == status && !simulation_end(philo->data))
        printf(RED "%-6ld" RESET "%d died 💀\n", elapsed, philo->id);
}

void	write_status(t_estatus status, t_philo *philo, bool debug)
{
	int elapsed;

	elapsed = gettime(MILLISECOND);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		protect_mutex_handle(&philo->data->print_mtx, LOCK);
		if ((status == FORK_RIGHT || status == FORK_LEFT)
			&& !simulation_end(philo->data))
			printf(GREY "%-6ld" RESET "%d has taken a fork\n", elapsed,
				philo->id);
		else if (status == EAT && !simulation_end(philo->data))
			printf(GREEN "%-6ld" RESET "%d is eating\n", elapsed, philo->id);
		else if (status == SLEEP && !simulation_end(philo->data))
			printf(CYAN "%-6ld" RESET "%d is sleeping\n", elapsed, philo->id);
		else if (status == THINK && !simulation_end(philo->data))
			printf(YELLOW "%-6ld" RESET "%d is thinking\n", elapsed, philo->id);
		else if (status == DIED && !simulation_end(philo->data))
			printf(RED "%-6ld" RESET "%d died\n", elapsed, philo->id);
	}
		protect_mutex_handle(&philo->data->print_mtx, UNLOCK);
}