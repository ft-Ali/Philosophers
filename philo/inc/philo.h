/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:22:58 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/02 14:29:47 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define GREY "\033[0;90m"
# define CYAN "\033[1;96m"
# define RESET "\033[0m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	t_fork				*left_fork;
	t_fork				*right_fork;
	int					eat_count;
	bool				full;
	long last_eat;    // last time the philo ate
	pthread_t thread; // thread of the philo
	t_data				*data;
}						t_philo;

/***
 * ./philo 5 800 200 200 [5]
 ****/

struct					s_data
{
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int limit_eat;      // optional [5]
	int timestamp;      // timestamp when the program started
	bool end_timestamp; // if philo died or all philo ate
	t_fork				*fork;
	t_philo				*philo;
};

/************** UTILS ****************/

void					error_exit(char *msg);

/************** PARSE ****************/
void					parse_input(t_data *data, char **argv);


#endif