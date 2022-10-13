/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:15:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 15:28:38 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* these functions are used to set the value of variables that are checked
 * or set throughout the simulation by more than one thread, typically by the
 * main thread (the philosopher) and her watcher thread. To do this in a safe
 * way (without data races), all of these values are protected by a
 * semaphore of their own with value one. Waiting for the semaphore is required
 * before getting or setting the value of the variable. After getting/setting,
 * the semaphore is being posted upon so that the other thread will be able
 * to access the variable.
 */

/* set the died variable to true
 */
void	set_died(t_ctrl *ctrl)
{
	sem_wait(ctrl->died_sem);
	ctrl->died = true;
	sem_post(ctrl->died_sem);
}

/* set the status variable in the control struct to status (either EATING or
 * OTHER).
 */
void	set_status(t_ctrl *ctrl, bool status)
{
	sem_wait(ctrl->status_sem);
	ctrl->status = status;
	sem_post(ctrl->status_sem);
}

/* set the time of the last meal to time in milliseconds
 */
void	set_last_meal(t_ctrl *ctrl, t_ms time)
{
	sem_wait(ctrl->last_meal_sem);
	ctrl->last_meal = time;
	sem_post(ctrl->last_meal_sem);
}

/* set the sated flag in the control struct to true
 */
void	set_sated(t_ctrl *ctrl)
{
	sem_wait(ctrl->sated_sem);
	ctrl->sated = true;
	sem_post(ctrl->sated_sem);
}
