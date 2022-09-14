/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:55:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/14 11:56:55 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


/* prints error message in case error was set. Returns if ctrl == NULL (nothing
 * has to be freed). In case of an invalid parameter, only the ctrl struct has
 * to be freed. Otherwise, mutexes must be destroyed and all arrays in the
 * ctrl-struct have to be freed. An error code is returned in case of error (2
 * for user error, 1 for system error). Zero is returned when no error occurred
 */
int	exit_program(t_ctrl *ctrl, int nu_forks, t_err *error)
{
	nu_forks--;
	if (*error)
		printf("%s %s\n", ERR, *error);
	if (ctrl == NULL)
		return (1);
	sem_close(ctrl->print);
	sem_close(ctrl->forks);
	sem_close(ctrl->last_meal_sem);
	sem_close(ctrl->status_sem);
	sem_close(ctrl->died_sem);
	sem_unlink("/tmp/last_meal_sem");
	sem_unlink("/tmp/status_sem");
	sem_unlink("/tmp/died_sem");
	sem_unlink("/tmp/print");
	sem_unlink("/tmp/forks");
	free(ctrl);
	if (*error)
		return (1);
	return (0);
}

