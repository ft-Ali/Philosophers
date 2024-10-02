/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:46:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/02 15:49:38 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*protect_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit("Malloc failed");
	return (ptr);
}

static void handle_mtx_err(int err, t_emutex action)
{
	if (err)
	{
		if (action == CREATE)
			error_exit("Mutex creation failed");
		else if (action == JOIN)
			error_exit("Thread join failed");
		else if (action == DETACH)
			error_exit("Thread detach failed");
	}
}

/***
 * MUTEX FUNCTIONS
 * LOCK, UNLOCK, INIT, DESTROY
 */

void	protect_mutex_handle(t_mtx *mutex, t_emutex action)
{
	if (action == LOCK)
		pthread_mutex_lock(mutex);
	else if (action == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (action == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (action == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		error_exit("Invalid mutex action");
}