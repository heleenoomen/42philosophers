/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 11:13:26 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* prints a log message and (importantly) sets the time of the last_action by
 * calling get_time(). To avoid messages getting mixed up form different threads/
 * processes printing at the same time, printing is protected by the print_sem
 * semaphore with value 1.
 */
void	print_action(t_ctrl *ctrl, char *action)
{
	sem_wait(ctrl->print_sem);
	ctrl->start_current_action = current_time();
	printf("%u %i %s\n", ctrl->start_current_action \
	- ctrl->start, ctrl->index, action);
	sem_post(ctrl->print_sem);
}

/* philosopher waits for two forks to become available (sem_wait on the forks
 * semaphore). After taking each for, a log message is printed.
 */
void	take_forks(t_ctrl *ctrl)
{
	sem_wait(ctrl->forks);
	print_action(ctrl, FORK);
	sem_wait(ctrl->forks);
	print_action(ctrl, FORK);
}

/* forks are put back on the table, represented by posting on the forks
 * semaphore. two more forks will now be available for other philosophers
 */
void	leave_forks(t_ctrl *ctrl)
{
	sem_post(ctrl->forks);
	sem_post(ctrl->forks);
}

/* philosopher first takes forks, then the EAT action is printed, set_status
 * is called to set the status to EATING and update the time of last meal.
 * Meals is increased by one and checked against max_meals to define if the
 * philosopher will be sated after this meal or not. Thread is send to sleep 
 * for time_eat milliseconds. If sated is true, philosopher posts on the sated
 * semaphore to wake up sat_watcher once all her sisters become sated too.
 */
void	ph_eat(t_ctrl *ctrl)
{
	bool	sated;

	take_forks(ctrl);
	print_action(ctrl, EAT);
	set_status(ctrl, ctrl->start_current_action);
	sated = ++ctrl->meals == ctrl->max_meals\
	&& ctrl->max_meals != -1;
	ph_usleep(ctrl, ctrl->time_eat);
	leave_forks(ctrl);
	if (sated)
		sem_post(ctrl->sated);
}

/* prints log message, sets status to OTHER and sends the main thread of the
 * process to sleep for time_sleep milliseconds.
 */
void	ph_sleep(t_ctrl *ctrl)
{
	print_action(ctrl, SLEEP);
	set_status(ctrl, 0);
	ph_usleep(ctrl, ctrl->time_sleep);
}
