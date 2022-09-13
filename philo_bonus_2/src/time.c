/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:20:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/13 13:38:07 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

/* Returns the current time in milliseconds */
t_ms	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ms) ((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

/* usleep is imprecise (since it stops a thread for AT LEAST n microseconds, but
 * possibly also longer). Therefore, we use a customi ph_usleep function. It
 * determines when the action will end (the time when the last action started +
 * the total time the action takes, and goes in a while loop until the current
 * time (gettime() is smaller than end_of_action. 
 * In between checking, the thread sleeps for 0.5 milliseconds to prevent the OS
 * from getting crazy. Death is checked in case a philosopheer dies in her
 * sleep.
 */
void	ph_usleep(t_ctrl *ctrl, t_ms time_action)
{
	t_ms	end_of_action;
	bool	died;

	end_of_action = gettime() + time_action;
	while ((gettime() < end_of_action))
	{
		sem_wait(ctrl->died_sem);
		died = ctrl->died;
		sem_post(ctrl->died_sem);
		if (died)
			break ;
		usleep (200);
	}
}

