/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/14 13:55:40 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* prints a log message and (importantly) sets the time of the last_action by
 * calling get_time(). To avoid messages getting mixed up form different threads/
 * processes printing at the same time, printing is protected by the print_sem
 * semaphore with value 1.
 * If the philosopher has already died, she is prevented from waiting for the
 * semaphore, because this semaphore whill be held by her watcher now. She will
 * thus be able to return to the caller function and eventually return to
 * run_philosophers routine from which she will join her watcher thread and
 * exit with DEATH status
 */
void	print_action(t_ctrl *ctrl, char *action)
{
	if (check_died(ctrl))
		return ;
	sem_wait(ctrl->print_sem);
	ctrl->start_current_action = gettime();
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

/* philosopher first takes forks, then the EAT action is printed, status is set
 * to EATING (meaning philosopher cannot die) and last_meal is set to
 * start_current_action. Meals is increased by one and checked against max_meals
 * to define if the philosopher will be sated after this meal or not. Main
 * thread is send to sleep for time_eat milliseconds. Afterwards, if sated is
 * true and max_meals parameter was entered, the philosopher will set the sated
 * flag to true, wait for the watcher thread to return, free her resources and
 * exit with SATED status.
 */
void	ph_eat(t_ctrl *ctrl)
{
	bool	sated;

	take_forks(ctrl);
	print_action(ctrl, EAT);
	set_status(ctrl, EATING);
	set_last_meal(ctrl, ctrl->start_current_action);
	sated = ++ctrl->meals == ctrl->max_meals;
	ph_usleep_eat(ctrl);
	leave_forks(ctrl);
	if (sated && ctrl->max_meals > -1)
	{
		set_sated(ctrl);
		//pthread_join(ctrl->watcher, NULL);
		usleep(500);
		free_ctrl(ctrl);
		exit(SATED);
	}
}

/* prints log message, sets status to OTHER (philosopher is no longer eating,
 * thus she can die) and sends the main thread of the process to sleep for
 * time_sleep milliseconds.
 */
void	ph_sleep(t_ctrl *ctrl)
{
	print_action(ctrl, SLEEP);
	set_status(ctrl, OTHER);
	ph_usleep_sleep(ctrl);
}
