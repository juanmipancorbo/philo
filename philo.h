/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:29:42 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/04 07:11:32 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <pthread.h> // mutex: init, destroy, lock, unlock
					// threads: create, join, detach 
# include <sys/time.h> // gettimeofday
# include <limits.h> // INT_MAX

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
/*                                 STRUCTS                                    */
/* ************************************************************************** */
typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

typedef struct s_fork
{
	t_mtx		fork;
	int			fork_id;
}				t_fork;

typedef struct s_philo
{
	int			id;
	int			full_of_food;
	long		meals_count;
	long		last_meal_time;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
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

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */
void	error_exit(const char *error);
void	*safe_malloc(size_t bytes);
