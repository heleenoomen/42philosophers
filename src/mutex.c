/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 10:44:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/10 17:24:36 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* initializes the mutex in the fork struct. Sets init to true when
 * initialization was succesful, and returns true. Sets error, sets init to
 * false and returns false when initialization of the mutex failed.
 */
bool	init_mutex(t_mutex *fork, t_err *error)
{
	if (pthread_mutex_init(&(fork->mutex), NULL))
	{
		*error = MUTEX_ERR;
		fork->init = false;
		return (false);
	}
	fork->init = true;
	return (true);	
}

/* once the forks array in the ctrl struct is succesfully allocated, the forks
 * are initialized one by one by calling init_mutex. If a fork is not initialized
 * succesfully (init_mutex returns false), error is set and we return. When all
 * forks in forks array are initialized, the print_lock mutex is initialized.
 */
void	init_all_mutexes(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	nu_forks;

	if (*error)
		return ;
	i = 0;
	nu_forks = ctrl->nu_philo;
	while (i < nu_forks)
	{
		init_mutex(ctrl->forks + i, error) == false;	
		i++;
	}
	init_mutex(&(ctrl->lock_print), error);
	init_mutex(&(ctrl->lock_death), error);
	init_mutex(&(ctrl->lock_sated), error);
}

