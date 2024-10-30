/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:22:58 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/18 13:20:59 by alsiavos         ###   ########.fr       */
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
	int					eat_count;
	bool				full;
	int					last_eat;
	t_mtx				philo_mtx;
	pthread_t			thread;
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
	int					error_exit;
	int					limit_eat;
	long				timestamp;
	bool				end_timestamp;
	bool				thread_ready;
	t_mtx				data_mtx;
	int					thread_count;
	pthread_t			monitor;
	t_mtx				print_mtx;
	t_fork				*forks;
	t_philo				*philo;
};

/************** UTILS ****************/

int						error_exit(char *msg);
void					think(t_philo *philo, bool presim);
void					*protect_malloc(size_t size);
void					free_data(t_data *data);
void					wait_trhead(t_data *data);
long					gettime(t_etime_code time_unit);
void					ft_usleep(int time, t_data *data);
void					write_status(t_estatus status, t_philo *philo,
							bool debug);
void					*start_sim(void *philo);
void					set_int(t_mtx *mtx, int *dest, int value);
void					increase_int(t_mtx *mtx, int *dest);
bool					all_threads_ready(t_mtx *mtx, int *threads,
							int philo_nbr);
void					*solo_p(void *data);
void					*monitor(void *data);
int						get_int(t_mtx *mtx, int *src);
void					write_status_debug(t_estatus status, t_philo *philo,
							long elapsed);

/************** PROCTECTED ****************/

void					protect_mutex_handle(t_mtx *mutex, t_emutex action);
void					*protect_malloc(size_t size);
int						t_handle(pthread_t *thread,
							void *(*start_routine)(void *), void *arg,
							int action);
void					handle_thread_err(int err, t_emutex action);

/************** PARSE ****************/

int						parse_input(t_data *data, char **argv);

/************** INIT ****************/

int						init_data(t_data *data);

/**************** ATTRIBUT MANAGER *************/

void					set_bool(t_mtx *mtx, bool *dest, bool value);
bool					get_bool(t_mtx *mtx, bool *src);
bool					simulation_end(t_data *data);
int						routine_start(t_data *data);
const char				*validate_number(const char *str);
const char				*validate_prefix(const char **str);
const char				*valide_input(const char *str);
bool					is_space(char c);
bool					is_digit(char c);
int						create_threads(t_data *data);
int						join_threads(t_data *data);
void					eat(t_philo *philo);

#endif