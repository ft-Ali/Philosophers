/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:22:58 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/14 00:57:16 by alsiavos         ###   ########.fr       */
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

# define RED "\033[1;31m"
# define GREY "\033[0;90m"
# define CYAN "\033[1;96m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define DEBUG 0

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

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
	long				eat_count;
	bool				full;
	long last_eat; // last time the philo ate
	t_mtx				philo_mtx;
	pthread_t thread; // thread of the philo
	t_data				*data;
}						t_philo;

/***
 * ./philo 5 800 200 200 [5]
 ****/

struct					s_data
{
	long					philo_nbr;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long limit_eat;      // optional [5]
	long timestamp;      // timestamp when the program started
	bool end_timestamp; // if philo died or all philo ate
	bool thread_ready;  // if all threads are ready
	t_mtx data_mtx;     // avoid data race
	long thread_count;   // count of threads
	pthread_t monitor;	  // monitor thread
	t_mtx print_mtx;    // print mutex
	t_fork				*forks;
	t_philo				*philo;
};

/************** UTILS ****************/

int						error_exit(char *msg);
void	think(t_philo *philo, bool presim);
void					*protect_malloc(size_t size);
void					free_data(t_data *data);
void					wait_trhead(t_data *data);
long					gettime(t_etime_code code);
void					ft_usleep(int time, t_data *data);
void					write_status(t_estatus status, t_philo *philo,
							bool debug);
void					*start_sim(void *philo);
void	set_int(t_mtx *mtx, long *dest, long value);
void increase_int(t_mtx *mtx, long *dest);
bool all_threads_ready(t_mtx *mtx, long *threads, long philo_nbr);
void *solo_p(void *data);
void *monitor(void *data);
long get_int(t_mtx *mtx, long *src);
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
bool					simulation_end(t_data *data);
void					*routine_start(t_data *data);

#endif