/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:55:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 13:54:53 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* destroys a mutex if it was initialized successfully
 */
void	destroy_mutex(t_mutex *mutex)
{
	if (mutex->init)
		pthread_mutex_destroy(&(mutex->mutex));
}

/* if the forks array is not NULL, all forks that were initialized are
 * destroyed. If the philos array is not NULL, all mutexes in all philo-structs
 * that were initialized are destroyed. Finally, the four remaining mutexes in
 * the ctrl are destroyed if they were successfully initialized
 */
void	destroy_all_mutexes(t_ctrl *ctrl)
{
	int		i;

	if (ctrl->forks != NULL)
	{
		i = -1;
		while (++i < ctrl->nu_philo)
			destroy_mutex(ctrl->forks + i);
	}
	if (ctrl->philos != NULL)
	{
		i = -1;
		while (++i < ctrl->nu_philo)
		{
			destroy_mutex(&(ctrl->philos[i].lock_meal));
			destroy_mutex(&(ctrl->philos[i].lock_status));
		}
	}
	destroy_mutex(&(ctrl->lock_death));
	destroy_mutex(&(ctrl->lock_sated));
	destroy_mutex(&(ctrl->lock_print));
	destroy_mutex(&(ctrl->lock_start));
}


/* prints error message in case error was set. Returns if ctrl == NULL (nothing
 * has to be freed). In case of an invalid parameter, only the ctrl struct has
 * to be freed. Otherwise, mutexes must be destroyed and all arrays in the
 * ctrl-struct have to be freed. An error code is returned in case of error (2
 * for user error, 1 for system error). Zero is returned when no error occurred
 */
int	exit_program(t_ctrl *ctrl, t_err *error)
{
	if (*error)
		printf("%s %s\n", ERR, *error);
	if (ctrl == NULL)
		return (1);
	if (ft_strcmp(INV_PH, *error) || ft_strcmp(INV_TIME, *error)
			|| ft_strcmp(INV_ME, *error))
	{
		free(ctrl);
		return (2);
	}
	destroy_all_mutexes(ctrl);
	free(ctrl->threads);
	free(ctrl->forks);
	free(ctrl->philos);
	free(ctrl);
	if (*error)
		return (1);
	return (0);
}

