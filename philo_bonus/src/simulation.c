/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 11:14:55 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* calls fork to create child process. If fork fails, sets error and calls
 * exit_program to directly exit the program in a clean way.
 * On success, returns the process id of the newly created child process
 * to the parent process and zero to the child process itself (return value
 * of fork())
 */
int	fork_handle_error(t_ctrl *ctrl, t_err *error)
{
	int	ret;

	ret = fork();
	if (ret == -1)
	{
		*error = FORK_ERR;
		exit_program(ctrl, error);
	}
	return (ret);
}

/* sets the start time of the simulation, and sets last_meal and last_action to
 * start_time. generates a process for each philosopher, calling
 * fork_handle_error. Saves the process id's of the child processes in the cpids
 * array. 
 * After creation of the threads, ripper is called to wait for the simulation
 * to end and thereupon terminate all child processes.
 */
void	start_simulation(t_ctrl *ctrl, t_err *error)
{
	int	i;

	i = -1;
	ctrl->start = current_time();
	ctrl->last_meal = ctrl->start;
	ctrl->start_current_action = ctrl->start;
	while (++i < ctrl->nu_philo)
	{
		ctrl->cpids[i] = fork_handle_error(ctrl, error);
		if (ctrl->cpids[i] == 0)
		{
			ctrl->index = i + 1;
			free(ctrl->cpids);
			run_philosophers(ctrl);
		}
	}
	jack_the_ripper(ctrl, error);
}
