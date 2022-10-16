/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:20:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 11:13:42 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Returns the current time in milliseconds */
t_ms	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ms)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

/* usleep is imprecise (since it stops a thread for AT LEAST n microseconds, but
 * possibly longer). Therefore, we use a custom ph_usleep function, which 
 * usleeps the process for only 0.2 milliseconds and then checks if the current
 * time, obtained by gettime(), is already smaller than end_of_action time.
 * end_of_action is obtained by adding the time the action takes to the
 * start time of the last action. (In between start_current_action and calling
 * the usleep function, some delays may have happened, for example, by setting
 * status or setting last meal, which require waiting for a semaphore).
 */
void	ph_usleep(t_ctrl *ctrl, t_ms time)
{
	t_ms	end_of_action;

	end_of_action = ctrl->start_current_action + time;
	while ((current_time() < end_of_action))
		usleep(200);
}
