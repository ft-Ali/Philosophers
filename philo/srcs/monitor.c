/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/10/10 23:16:39 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/10 23:16:39 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Routine pour un philosophe solitaire.
 *
 * Ce philosophe attend que la simulation commence, mange une fois,
 * puis attend que la simulation se termine.
 *
 * @param data Pointeur vers les données du philosophe.
 * @return NULL
 */

void	*solo_p(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_trhead(philo->data);
	set_int(&philo->data->data_mtx, &philo->last_eat, gettime(MILLISECOND));
	increase_int(&philo->data->data_mtx, &philo->data->thread_count);
	write_status(FORK_RIGHT, philo, DEBUG);
	while (!simulation_end(philo->data))
		usleep(200);
	return (NULL);
}

/**
 * @brief Fonction principale de la simulation pour chaque philosophe.
 *
 * Chaque philosophe attend le début de la simulation, mange,
 * dort, puis pense. Cela continue jusqu'à ce que la simulation
 * prenne fin ou que le philosophe soit plein.
 *
 * @param philo Pointeur vers la structure du philosophe.
 * @return NULL
 */

void	*start_sim(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	wait_trhead(p->data);
	set_int(&p->philo_mtx, &p->last_eat, gettime(MILLISECOND));
	increase_int(&p->data->data_mtx, &p->data->thread_count);
	while (!simulation_end(p->data))
	{
		if (p->full)
			break ;
		eat(p);
		write_status(SLEEP, p, DEBUG);
		ft_usleep(p->data->time_to_sleep, p->data);
		think(p, false);
	}
	return (NULL);
}

/**
 * @brief Vérifie si un philosophe est mort en comparant le temps écoulé
 * depuis son dernier repas avec le temps limite avant la mort.
 *
 * Cette fonction détermine si le philosophe est mort en vérifiant si
 * le temps écoulé depuis son dernier repas dépasse le temps limite
 * défini par `time_to_die`. Elle commence par vérifier si le philosophe
 * est déjà rassasié et retourne faux si c'est le cas. Si le
 * philosophe a mangé, elle calcule le temps écoulé depuis son dernier
 * repas et compare ce temps avec `time_to_die`. Si le temps écoulé
 * est supérieur à `time_to_die`, la fonction retourne vrai, indiquant
 * que le philosophe est considéré comme mort.
 *
 *
 * @param philo Pointeur vers la structure du philosophe à vérifier.
 * @return true si le philosophe est mort, false sinon.
 */

static bool	philo_died(t_philo *philo)
{
	int	time;
	int	t_die;

	if (get_bool(&philo->data->data_mtx, &philo->full))
		return (false);
	time = gettime(MILLISECOND) - get_int(&philo->data->data_mtx,
			&philo->last_eat);
	t_die = philo->data->time_to_die / 1e3;
	if (time > t_die)
		return (true);
	return (false);
}
/**
 * @brief Fonction du thread de surveillance des philosophes.
 *
 * Cette fonction surveille en continu l'état des philosophes et
 * détermine si l'un d'eux est mort. Si un philosophe meurt, cela
 * met fin à la simulation et enregistre l'événement.
 *
 * @param data Pointeur vers la structure de données de la simulation.
 * @return NULL.
 */

void	*monitor(void *data)
{
	t_data	*d;
	int		i;

	d = (t_data *)data;
	while (!all_threads_ready(&d->data_mtx, &d->thread_count, d->philo_nbr))
		;
	while (!simulation_end(d))
	{
		i = -1;
		while (++i < d->philo_nbr && !simulation_end(d))
		{
			if (philo_died(d->philo + i))
			{
				set_bool(&d->data_mtx, &d->end_timestamp, true);
				write_status(DIED, d->philo + i, DEBUG);
			}
		}
	}
	return (NULL);
}
