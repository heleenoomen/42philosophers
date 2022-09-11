/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:20:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 11:20:01 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/* Gets the current time in milliseconds */
t_ms	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/* Sets the end_of_action, which is the time the current action started 
 * (last_action) plus the time reserved for the action (time_action, i.e. 
 * time_sleep or time_eat). Using usleep(time_action) would be imprecise, since
 * usleep stops the thread for AT LEAST time_action. Therefore, we rather stop
 * the thread for 0.5 ms at a time and then check if it has already reached
 * end_of_action If in another philosopher dies, the action is stopped
 * immediately.
 */
void	ph_usleep(t_philo *philo, t_ms time_action)
{
	t_ms	end_of_action;

	end_of_action = philo->last_action + time_action;
	while ((gettime() < end_of_action))
	{
		if (check_death(philo->ctrl))
			break ;
		usleep (500);
	}
}

