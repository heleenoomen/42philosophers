/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:48:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/15 23:38:37 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* returns the timestamp of the last_meal
 */
t_ms	time_last_meal(t_ctrl *ctrl)
{
	t_ms	time;
	bool	status;

	sem_wait(ctrl->last_meal_sem);
	status = ctrl->status;
	if (status == OTHER)
		time = ctrl->last_meal;
	sem_post(ctrl->last_meal_sem);
	if (status == EATING)
		time = gettime();
	return (time);
}
