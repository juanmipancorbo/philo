/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:29:42 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/07 19:37:05 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <pthread.h> // mutex: init, destroy, lock, unlock
					// threads: create, join, detach 
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX
# include <errno.h>

/* ************************************************************************** */
/*                           ANSI ESCAPE SECUENCES                            */
/* ************************************************************************** */
# define RST 	"\033[0m"
# define R 		"\033[1;31m"
# define G 		"\033[1;32m"
# define Y 		"\033[1;33m"
# define B 		"\033[1;34m"
# define M 		"\033[1;35m"
# define C 		"\033[1;36m"
# define W 		"\033[1;37m"

/* ************************************************************************** */
/*                                 OPCODE                                     */
/* ************************************************************************** */

typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}				t_opcode;

/* ************************************************************************** */
/*                                 STRUCTS                                    */
/* ************************************************************************** */
typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

typedef struct s_fork
{
	t_mtx		mtx;
	int			id;
}				t_fork;

typedef struct s_philo
{
	int			id;
	int			full_of_food;
	long		meals_count;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_table		*table;
}				t_philo;

struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meals;
	long	start_time; 
	int		end_simulation;
	t_fork	*forks;
	t_philo	*philos;
};

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */
void	to_parse(t_table *table, char **argv);
void	to_init(t_table *table);
void	to_exit(const char *error);
void	*to_malloc(size_t bytes);
void	mutex_handler(t_mtx *mutex, t_opcode opcode);
void	thread_handler(pthread_t *thread, void *(*ft)(void*),
							 void *data, t_opcode opcode); 
