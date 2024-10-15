/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:30:33 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/15 11:34:21 by alsiavos         ###   ########.fr       */
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

int	get_int(t_mtx *mtx, int *src)
{
	int	ret;

	protect_mutex_handle(mtx, LOCK);
	ret = *src;
	protect_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void	set_int(t_mtx *mtx, int *dest, int value)
{
	protect_mutex_handle(mtx, LOCK);
	*dest = value;
	protect_mutex_handle(mtx, UNLOCK);
}

bool	simulation_end(t_data *data)
{
	return (get_bool(&data->data_mtx, &data->end_timestamp));
}
