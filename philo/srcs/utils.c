/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:52:02 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/18 11:47:10 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	gettime(t_etime_code code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_exit("gettimeofday() failed"));
	if (SECOND == code)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (MILLISECOND == code)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else if (MICROSECOND == code)
		return (tv.tv_sec * 1000000 + tv.tv_usec);
	else
		return (error_exit("Invalid time code"));
	return (42);
}

int	error_exit(char *msg)
{
	printf(RED "🚨 %s 🚨\n" RESET, msg);
	return (1);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (!data || !data->philo)
		return ;
	while (++i < data->philo_nbr)
	{
		protect_mutex_handle(&data->philo[i].philo_mtx, DESTROY);
	}
	protect_mutex_handle(&data->data_mtx, DESTROY);
	protect_mutex_handle(&data->print_mtx, DESTROY);
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
}

void	ft_usleep(int time, t_data *data)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < time)
	{
		if (simulation_end(data))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = time - elapsed;
		if (rem > 10000)
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECOND) - start < time)
				;
		}
	}
}
