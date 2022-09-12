/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:07:13 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/12 17:29:25 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.c"

void	watcher(void *args)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *) args;

void	child_process(t_ctrl *ctrl)
{
	pthread_create(&watcher_thread, NULL, &watcher, (void *)ctrl);
	philo_runi(ctrl);
}

void	parent_process(t_ctrl *ctrl)
{
	int	i;
	int	status;

	i = -1;
	/* put semaphore creation to wait */
	while (++i < ctrl->nu_philos)
	{
		ctrl->cpids[i] = fork();
		if (ctrl->cpids[i] == -1)
			break ;
		if (ctrl->cpids[i] == 0)
		{
			philosophers(ctrl);
			exit(0);
		}
	}
	/* put semaphore creation to go */
	/* lock death semaphore*/
	/* wait until death semaphore is unlocked */
	sem_wait(death_semaphore);
	kill(0, SIGTERM);
	exit_program(ctrl);	
}
