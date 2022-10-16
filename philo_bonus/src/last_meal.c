/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_meal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:48:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 11:15:09 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* returns the timestamp of the last_meal to watcher.
 * in case philosopher is EATING, returns current time
 * so that watcher will not kill eating philosophers.
 */
t_ms	get_time_last_meal(t_ctrl *ctrl)
{
	t_ms	time;
	bool	status;

	sem_wait(ctrl->last_meal_sem);
	status = ctrl->status;
	if (status == OTHER)
		time = ctrl->last_meal;
	sem_post(ctrl->last_meal_sem);
	if (status == EATING)
		time = current_time();
	return (time);
}

/* changes the status form EATING ot OTHER or vice versa.
 * if the new status is EATING, updates the time of the last
 * meal.
 */
void	set_status(t_ctrl *ctrl, t_ms time)
{
	sem_wait(ctrl->last_meal_sem);
	ctrl->status = !ctrl->status;
	if (ctrl->status == EATING)
		ctrl->last_meal = time;
	sem_post(ctrl->last_meal_sem);
}
