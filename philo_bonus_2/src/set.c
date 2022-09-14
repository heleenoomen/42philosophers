/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:15:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/14 11:46:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	set_died(t_ctrl *ctrl)
{
	sem_wait(ctrl->died_sem);
	ctrl->died = true;
	sem_post(ctrl->died_sem);
}

void	set_status(t_ctrl *ctrl, bool status)
{
	sem_wait(ctrl->status_sem);
	ctrl->status = status;
	sem_post(ctrl->status_sem);
}

void	set_last_meal(t_ctrl *ctrl, t_ms time)
{
	sem_wait(ctrl->last_meal_sem);
	ctrl->last_meal = time;
	sem_post(ctrl->last_meal_sem);
}

