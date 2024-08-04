/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:09:16 by jpancorb          #+#    #+#             */
/*   Updated: 2024/08/03 00:33:01 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_error(char *err, t_table *table)
{
	if (err)
		to_exit(err, table);
}

static void	mutex_error(int status, t_opcode opcode, t_table *table)
{
	if (status == 0)
		return ;
	if (EINVAL == status)
	{
		if (LOCK == opcode || UNLOCK == opcode || DESTROY == opcode)
			to_exit("The value especified by mutex is invalid.", table);
		else if (INIT == opcode)
			to_exit("The value especified by attr is invalid.", table);
	}
	else if (EDEADLK == status)
		to_exit("A deadlock would occur if the thread blocked "
			"waiting for mutex.", table);
	else if (EPERM == status)
		to_exit("The current thread does not hold a lock on mutex.", table);
	else if (ENOMEM == status)
		to_exit("The process cannot allocate enough memory to "
			"create another mutex.", table);
	else if (EBUSY == status)
		to_exit("Mutex is locked.", table);
}

void	mutex_handler(t_mtx *mutex, t_opcode opcode, t_table *table)
{
	if (LOCK == opcode)
		mutex_error(pthread_mutex_lock(mutex), opcode, table);
	else if (UNLOCK == opcode)
		mutex_error(pthread_mutex_unlock(mutex), opcode, table);
	else if (INIT == opcode)
		mutex_error(pthread_mutex_init(mutex, NULL), opcode, table);
	else if (DESTROY == opcode)
		mutex_error(pthread_mutex_destroy(mutex), opcode, table);
}

static char	*thread_error(int status, t_opcode opcode)
{
	char	*err;

	err = NULL;
	if (status == 0)
		return (NULL);
	if (EAGAIN == status)
		err = "No resources to create another thread.";
	else if (EPERM == status)
		err = "The caller does not have appropriate permission.";
	else if (EINVAL == status)
	{
		if (CREATE == opcode)
			err = "The value especified by attr is invalid.";
		else if (JOIN == opcode)
			err = "The value especified by thread is not joinable.";
	}
	else if (ESRCH == status)
		err = "No thread could be found corresponding to that specified "
			"by the given thread ID, thread.";
	else if (EDEADLK == status)
		err = "A deadlock was detected or the value of thread specifies the "
			"calling thread.";
	return (err);
}

char	*thread_handler(pthread_t *thread, void *(*ft)(void *),
						void *data, t_opcode opcode)
{
	char	*err;

	err = NULL;
	if (CREATE == opcode)
		err = thread_error(pthread_create(thread, NULL, ft, data), opcode);
	else if (JOIN == opcode)
		err = thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		thread_error(pthread_detach(*thread), opcode);
	return (err);
}
