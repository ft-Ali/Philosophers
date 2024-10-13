/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:30:33 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/13 22:08:57 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	protect_mutex_handle(mtx, LOCK);
	*dest = value;
	protect_mutex_handle(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *src)
{
	bool	ret;

	protect_mutex_handle(mtx, LOCK);
	ret = *src;
	protect_mutex_handle(mtx, UNLOCK);
	return (ret);
}
long get_int(t_mtx *mtx, long *src)
{
	long ret;

	protect_mutex_handle(mtx, LOCK);
	ret = *src;
	protect_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void	set_int(t_mtx *mtx, long *dest, long value)
{
	protect_mutex_handle(mtx, LOCK);
	*dest = value;
	protect_mutex_handle(mtx, UNLOCK);
}

bool	simulation_end(t_data *data)
{
	return (get_bool(&data->data_mtx, &data->end_timestamp));
}
