/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:48:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/17 14:59:35 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_died(t_ctrl *ctrl)
{
	bool	ret;

	sem_wait(ctrl->died_sem);
	ret = ctrl->died;
	sem_post(ctrl->died_sem);
	return (ret);
}

bool	check_status(t_ctrl *ctrl)
{
	bool	ret;

	sem_wait(ctrl->status_sem);
	ret = ctrl->status;
	sem_post(ctrl->status_sem);
	return (ret);
}

t_ms	time_last_meal(t_ctrl *ctrl)
{
	t_ms	time;

	sem_wait(ctrl->last_meal_sem);
	time = ctrl->last_meal;
	sem_post(ctrl->last_meal_sem);
	return (time);
}

