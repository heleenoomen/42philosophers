/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:55:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/19 18:52:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_sem(sem_t *semaphore, char *name)
{
	if (semaphore != SEM_FAILED)
	{
		sem_close(semaphore);
		sem_unlink(name);
	}
}

void	kill_child_processes(t_ctrl *ctrl)
{
	int	i;

	i = -1;
	while (++i < ctrl->nu_philo)
	{
		if (ctrl->cpids[i] != 0)
		{
			kill(ctrl->cpids[i], SIGKILL);
			ctrl->cpids[i] = 0;
		}
	}
}

int	exit_program(t_ctrl *ctrl, t_err *error)
{
	if (*error)
		printf("%s %s\n", ERR, *error);
	if (ctrl == NULL)
		return (1);
	if (!ft_strcmp(*error, FORK_ERR))
		kill_child_processes(ctrl);
	if (!ft_strcmp(*error, INV_TIME) || !ft_strcmp(*error, INV_PH)
			|| !ft_strcmp(*error, INV_ME) || !ft_strcmp(*error, NO_PH))
	{
		free(ctrl);
		return (2);
	}
	close_sem(ctrl->print, "/tmp/print");
	close_sem(ctrl->forks, "/tmp/forks");
	close_sem(ctrl->last_meal_sem, "/tmp/last_meal_sem");
	close_sem(ctrl->status_sem, "/tmp/status_sem");
	close_sem(ctrl->died_sem, "/tmp/died_sem");
	free(ctrl->cpids);
	free(ctrl);
	if (*error)
		return (1);
	return (0);
}

