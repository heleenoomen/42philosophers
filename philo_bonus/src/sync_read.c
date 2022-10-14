/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:48:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/15 01:28:48 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* these functions are used to get the value of variables that are checked
 * or set throughout the simulation by more than one thread, typically by the
 * main thread (the philosopher) and her watcher thread. To do this in a safe
 * way (without data races), all of these values are protected by a
 * semaphore of their own with value one. Waiting for the semaphore is required
 * before getting or setting the value of the variable. After getting/setting,
 * the semaphore is being posted upon so that the other thread will be able
 * to access the variable.
 */

/* returns true if died flag was set, returns false if died flag was not set
 */
bool	simulation(t_ctrl *ctrl)
{
	bool	ret;

	sem_wait(ctrl->died_sem);
	ret = ctrl->simulation;
	sem_post(ctrl->died_sem);
	return (ret);
}

/* returns the value of the status flag (either EATING or OTHER)
 */
bool	check_status(t_ctrl *ctrl)
{
	bool	ret;

	sem_wait(ctrl->status_sem);
	ret = ctrl->status;
	sem_post(ctrl->status_sem);
	return (ret);
}

/* returns the timestamp of the last_meal
 */
t_ms	time_last_meal(t_ctrl *ctrl)
{
	t_ms	time;

	sem_wait(ctrl->last_meal_sem);
	time = ctrl->last_meal;
	sem_post(ctrl->last_meal_sem);
	return (time);
}
