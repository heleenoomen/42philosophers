/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saturation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:01:17 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 00:24:20 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	saturation(t_ctrl *ctrl)
{
	int	i;

	if (ctrl->max_meals == -1)
		return ;
	i = -1;
	while (++i < ctrl->nu_philo)
		sem_wait(ctrl->sated);
	sem_post(ctrl->stop_all);
	sem_post(ctrl->stop_all);
}

void	wait_for_child_processes(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	status;

	i = -1;
	while (++i < ctrl->nu_philo)
	{
		waitpid(0, &status, 0);
		if (WIFSIGNALED(status))
			status = 0;
		else if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status && *error == NULL)
			*error = THREAD_ERR;
	}
}

void	kill_all(t_ctrl *ctrl, t_err *error)
{
	int	i;

	i = -1;
	while(++i < ctrl->nu_philo)
		kill(ctrl->cpids[i], SIGTERM);
	wait_for_child_processes(ctrl, error);
}

void	big_watcher(t_ctrl *ctrl, t_err *error)
{
	int	i;

	if (pthread_create(&ctrl->watcher2, NULL, (void *)&saturation,\
	(void *)ctrl))
	{
		*error = THREAD_ERR;
		kill_all(ctrl, error);
		return ;
	}
	sem_wait(ctrl->stop_all);
	kill_all(ctrl, error);
	i = -1;
	while (++i < ctrl->nu_philo)
		sem_post(ctrl->sated);
	pthread_join(ctrl->watcher2, NULL);
}
