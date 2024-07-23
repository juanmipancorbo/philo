/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:09:16 by jpancorb          #+#    #+#             */
/*   Updated: 2024/07/23 20:48:05 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_exit(const char *error)
{
	printf(R"%s\n"RST, error);
	exit(EXIT_FAILURE);
}

static void	mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status)
	{
		if (LOCK == opcode || UNLOCK == opcode || DESTROY == opcode)
			to_exit("The value especified by mutex is invalid.");
		else if (INIT == opcode)
			to_exit("The value especified by attr is invalid.");
	}
	else if (EDEADLK == status)
		to_exit("A deadlock would occur if the thread blocked "
			"waiting for mutex.");
	else if (EPERM == status)
		to_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		to_exit("The process cannot allocate enough memory to "
			"create another mutex.");
	else if (EBUSY == status)
		to_exit("Mutex is locked.");
}

void	mutex_handler(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		to_exit("Wrong opcode for \'mutex_handler\'\n"
			W"use <LOCK> <UNLOCK> <INIT> <DESTROY>"RST);
}

static void	thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		to_exit("No resources to create another thread.");
	else if (EPERM == status)
		to_exit("The caller does not have appropriate permission.");
	else if (EINVAL == status)
	{
		if (CREATE == opcode)
			to_exit("The value especified by attr is invalid.");
		else if (JOIN == opcode || DETACH == opcode)
			to_exit("The value especified by thread is not joinable.");
	}
	else if (ESRCH == status)
		to_exit("No thread could be found corresponding to that specified "
			"by the given thread ID, thread.");
	else if (EDEADLK == status)
		to_exit("A deadlock was detected or the value of thread specifies the "
			"calling thread.");
}

void	thread_handler(pthread_t *thread, void *(*ft)(void *),
						void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		thread_error(pthread_create(thread, NULL, ft, data), opcode);
	else if (JOIN == opcode)
		thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		thread_error(pthread_detach(*thread), opcode);
	else
		to_exit("Wrong opcode for \'thread_handler\'\n"
			W"use <CREATE> <JOIN> <DETACH>"RST);
}
