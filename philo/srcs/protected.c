/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:46:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/14 14:53:56 by alsiavos         ###   ########.fr       */
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

static void	handle_mtx_err(int err, t_emutex action)
{
	if (err == 0)
		return ;
	if (err && (action == LOCK || action == UNLOCK))
		error_exit("Mutex lock/unlock failed");
	else if (err && action == INIT)
		error_exit("Mutex init failed");
	else if (err && action == DESTROY)
		error_exit("Mutex Free");
}

void	protect_mutex_handle(t_mtx *mutex, t_emutex action)
{
	if (mutex == NULL)
		error_exit("Mutex pointer is NULL");
	if (action == LOCK)
		handle_mtx_err(pthread_mutex_lock(mutex), action);
	else if (action == UNLOCK)
		handle_mtx_err(pthread_mutex_unlock(mutex), action);
	else if (action == INIT)
		handle_mtx_err(pthread_mutex_init(mutex, NULL), action);
	else if (action == DESTROY)
		handle_mtx_err(pthread_mutex_destroy(mutex), action);
	else
		error_exit("Invalid mutex action");
}

void	handle_thread_err(int err, t_emutex action)
{
	if (err == 0)
		return ;
	if (err && action == CREATE)
		error_exit("Thread creation failed");
	else if (err && action == JOIN)
		error_exit("Thread join failed");
	else if (err && action == DETACH)
		error_exit("Thread detach failed");
}

void	protect_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_emutex action)
{
	if (action == CREATE)
		handle_thread_err(pthread_create(thread, NULL, foo, data), action);
	else if (action == JOIN)
		handle_thread_err(pthread_join(*thread, NULL), action);
	else if (action == DETACH)
		handle_thread_err(pthread_detach(*thread), action);
	else
		error_exit("Invalid thread action");
}
