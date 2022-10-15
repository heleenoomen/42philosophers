/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:15:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/15 23:41:58 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* set the time of the last meal to time in milliseconds
 */
void	set_last_meal(t_ctrl *ctrl, t_ms time)
{
	sem_wait(ctrl->last_meal_sem);
	ctrl->status = !ctrl->status;
	if (ctrl->status == EATING)
		ctrl->last_meal = time;
	sem_post(ctrl->last_meal_sem);
}
