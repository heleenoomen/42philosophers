/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:20:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/15 13:04:28 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Returns the current time in milliseconds */
t_ms	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ms)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

/* usleep is imprecise (since it stops a thread for AT LEAST n microseconds, but
 * possibly longer). Therefore, we use two custom ph_usleep functions, which 
 * usleeps the process for only 0.2 milliseconds and then checks if the current
 * time (obtained by gettime()) is already smaller than end_of_action time.
 * end_of_action is obtained by adding the time the action takes to the
 * start time of the last action. (In between start_current_action and calling
 * the usleep function, some delays may have happened, for example, by setting
 * status or setting last meal, which require waiting for a semaphore).
 * ph_usleep_sleep checks at every iteration if the philosopher has died, since
 * philosophers may die while sleeping.
 */
void	ph_usleep_check(t_ctrl *ctrl, t_ms time)
{
	t_ms	end_of_action;

	end_of_action = ctrl->start_current_action + time;
	while ((gettime() < end_of_action))
	{
		if (!simulation(ctrl))
			break ;
		usleep (200);
	}
}

/* same as ph_usleep_sleep, but without calling costly sim_over function,
 * since philosophers cannot die while eating anyway.
 */
void	ph_usleep_eat(t_ctrl *ctrl)
{
	t_ms	end_of_action;

	end_of_action = ctrl->start_current_action + ctrl->time_eat;
	while ((gettime() < end_of_action))
		usleep(200);
}
