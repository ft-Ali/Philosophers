/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:22:58 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/10 16:44:50 by alsiavos         ###   ########.fr       */
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
# define DEBUG 0

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	FORK_RIGHT,
	FORK_LEFT,
	DIED,
}						t_estatus;

typedef enum e_mutex
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_emutex;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_etime_code;

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
	int last_eat; // last time the philo ate
	t_mtx				philo_mtx;
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
	bool thread_ready;  // if all threads are ready
	t_mtx data_mtx;     // avoid data race
	t_mtx print_mtx;    // print mutex
	t_fork				*forks;
	t_philo				*philo;
};

/************** UTILS ****************/

int						error_exit(char *msg);
void					*protect_malloc(size_t size);
void					free_data(t_data *data);
void					wait_trhead(t_data *data);
long					gettime(t_etime_code code);
void					ft_usleep(int time, t_data *data);
void					write_status(t_estatus status, t_philo *philo,
							bool debug);
void					*start_sim(void *philo);
void					set_int(t_mtx *mtx, int *dest, int value);

/************** PROCTECTED ****************/

void					protect_mutex_handle(t_mtx *mutex, t_emutex action);
void					*protect_malloc(size_t size);
void					protect_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_emutex action);
void					handle_thread_err(int err, t_emutex action);

/************** PARSE ****************/

void					parse_input(t_data *data, char **argv);

/************** INIT ****************/

void					init_data(t_data *data);

/**************** ATTRIBUT MANAGER *************/

void					set_bool(t_mtx *mtx, bool *dest, bool value);
bool					get_bool(t_mtx *mtx, bool *src);
void					set_int(t_mtx *mtx, int *dest, int value);
bool					simulation_end(t_data *data);
void					*routine_start(t_data *data);

#endif