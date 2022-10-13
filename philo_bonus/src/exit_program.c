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

void	close_all_semaphores(t_ctrl *ctrl)
{
	close_sem(ctrl->print_sem, "print_sem");
	close_sem(ctrl->forks, "forks");
	close_sem(ctrl->last_meal_sem, "last_meal_sem");
	close_sem(ctrl->status_sem, "status_sem");
	close_sem(ctrl->died_sem, "died_sem");
	close_sem(ctrl->sated_sem, "sated_sem");
}

void	free_ctrl(t_ctrl *ctrl)
{
	free(ctrl->cpids);
	free(ctrl);
}

void	kill_child_processes(t_ctrl *ctrl)
{
	int	i;

	i = -1;
	while (++i < ctrl->nu_philo)
	{
		if (ctrl->cpids[i] != 0)
		{
			kill(ctrl->cpids[i], SIGTERM);
			ctrl->cpids[i] = 0;
		}
	}
}

int	exit_program(t_ctrl *ctrl, t_err *error)
{
	if (*error && ft_strcmp(*error, START_SATED))
		printf("%s %s\n", ERR, *error);
	if (ctrl == NULL)
		return (1);
	if (!ft_strcmp(*error, FORK_ERR))
		kill_child_processes(ctrl);
	if (!ft_strcmp(*error, INV_TIME) || !ft_strcmp(*error, INV_PH)
			|| !ft_strcmp(*error, INV_ME))
	{
		free_ctrl(ctrl);
		return (2);
	}
	if (!ft_strcmp(*error, NO_PH) || !ft_strcmp(*error, START_SATED))
	{
		free_ctrl(ctrl);
		return (0);
	}
	close_all_semaphores(ctrl);
	free_ctrl(ctrl);
	if (*error)
		return (1);
	return (0);
}

