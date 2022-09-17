/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:55:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/16 16:07:11 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_sem(sem_t *semaphore, char *name)
{
	if (semaphore != SEM_FAILED)
	{
		close(semaphore);
		sem_unlink(name);
	}
}

int	exit_program(t_ctrl *ctrl, t_err *error)
{
	if (*error)
		printf("%s %s\n", ERR, *error);
	if (ctrl == NULL)
		return (1);
	close_sem(ctrl->print, "/tmp/print");
	close_sem(ctrl->forks, "/tmp/forks");
	close_sem(ctrl->last_meal_sem, "/tmp/last_meal_sem");
	close_sem(ctrl->status_sem, "/tmp/status_sem");
	close_sem(ctrl->died_sem, "/tmp/died_sem");
	free(ctrl);
	if (*error)
		return (1);
	return (0);
}

