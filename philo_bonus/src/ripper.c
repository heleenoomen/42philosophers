/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:01:17 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 10:59:20 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* thread routine for sat_watcher thread created by ripper. If max_meals was
 * not entered by user, returns immediately. Otherwise, waits until all
 * philosophers post on the sated semaphore, then posts on the stop_all
 * semaphore to wake up ripper. (Ripper will post itself on the sated semaphore
 * in case of death, so that the thread will return in that case).
*/
void	saturation(t_ctrl *ctrl)
{
	int	i;

	if (ctrl->max_meals == -1)
		return ;
	i = -1;
	while (++i < ctrl->nu_philo)
		sem_wait(ctrl->sated);
	sem_post(ctrl->stop_all);
}

/* wait for every child process that was succesfully created
 * (child pid > 0).
 */
void	wait_for_child_processes(t_ctrl *ctrl)
{
	int	i;
	int	status;

	i = -1;
	while (++i < ctrl->nu_philo)
	{
		if (ctrl->cpids[i] > 0)
			waitpid(0, &status, 0);
	}
}

/* sends the SIGTERM signal to every childprocess that was successfully created
 * (child pid > 0). Waits for all succesfully created child processes before 
 * returning.
 */
void	kill_all(t_ctrl *ctrl)
{
	int	i;

	i = -1;
	while(++i < ctrl->nu_philo)
	{
		if (ctrl->cpids[i] > 0)
			kill(ctrl->cpids[i], SIGTERM);
	}
	wait_for_child_processes(ctrl);
}

/* generates a sat_watcher thread which will oversee if all philosophers
 * become sated. Waits for the stop_all sem to be posted upon, then
 * kills all child processes, posts itself on the sated semaphore to 
 * make sat_watcher return and joins sat_watcher thread
 */
void	jack_the_ripper(t_ctrl *ctrl, t_err *error)
{
	int			i;
	pthread_t	sat_watcher;

	if (pthread_create(&sat_watcher, NULL, (void *)&saturation,\
	(void *)ctrl))
	{
		*error = THREAD_ERR;
		kill_all(ctrl);
		return ;
	}
	sem_wait(ctrl->stop_all);
	kill_all(ctrl);
	i = -1;
	while (++i < ctrl->nu_philo)
		sem_post(ctrl->sated);
	pthread_join(sat_watcher, NULL);
}
