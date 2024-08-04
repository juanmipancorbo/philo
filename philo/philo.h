/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb < jpancorb@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:29:42 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/04 15:01:04 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <pthread.h> //mutex: init, destroy, lock, unlock
						//threads: create, join
# include <sys/time.h> //gettimeofday
# include <limits.h> //INT_MAX
# include <string.h> // memset
//# include <errno.h> //error macros

/* ************************************************************************** */
/*                           ANSI ESCAPE SECUENCES                            */
/* ************************************************************************** */
# define RST		"\033[0m"
# define R 			"\033[1;31m"
# define G 			"\033[1;32m"
# define Y 			"\033[1;33m"
# define B 			"\033[1;34m"
# define M 			"\033[1;35m"
# define C 			"\033[1;36m"
# define W 			"\033[1;37m"
# define DEBUG_MODE	0

/* ************************************************************************** */
/*                                 OPCODE                                     */
/* ************************************************************************** */
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}				t_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}				t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}				t_time_code;

/* ************************************************************************** */
/*                                 STRUCTS                                    */
/* ************************************************************************** */
typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx		mtx;
	int			id;
}				t_fork;

typedef struct s_philo
{
	int			id;
	long		full_of_food;
	long		meals_count;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		mtx;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		max_meals;
	long		start_time;
	long		end_time;
	long		threads_ready;
	long		nbr_threads_running;
	pthread_t	monitor;
	t_mtx		table_mtx;
	t_mtx		print_mtx;
	t_fork		*forks;
	t_philo		*philos;
}				t_table;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */
int		to_parse(t_table *table, char **argv);
int		to_exit(const char *error, t_table *table);
char	*thread_handler(pthread_t *thread, void *(*ft)(void *),
			void *data, t_opcode opcode);
int		to_dinner(t_table *table);
void	to_set(t_mtx *mutex, long *dst, long value, t_table *table);
long	to_get(t_mtx *mutex, long *value, t_table *table);
int		to_finish(t_table *table);
void	to_wait(t_table *table);
long	to_time(t_time_code time_code, t_table *table);
void	precise_usleep(long usec, t_table *table);
void	print_status(t_status status, t_philo *philo, int debug,
			t_table *table);
int		all_threads_running(t_mtx *mutex, long *threads, long philo_nbr,
			t_table *table);
void	to_increase(t_mtx *mutex, long *value, t_table *table);
void	*to_monitor(void *data);
void	to_clean(t_table *table);
void	to_think(t_philo *philo, int to_detach);
void	to_detach(t_philo *philo);
void	to_error(char *err, t_table *table);

#endif