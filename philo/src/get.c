/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:48:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 16:23:16 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Every shared variable that is modified or checked by several threads is
 * protected by a mutex of its own to avoid dataraces.
 * (For example: when the main thread is busy setting 'death' to true, the 
 * lock_death mutex is locked, and threads wanting to check the death parameter
 * have to wait until the main thread has finished updating the value).
 * All 'set_ / increment_' functions (see set.c) have their 'check_'
 * counterpart, where the same mutex is used. While the value is being changed,
 * threads who want to read the value have to wait until the writing thread
 * unlocks the corresponding mutex and vice versa.
 */

/* returns true if death has occurred at the table. Otherwise returns false
 */
bool	check_death(t_ctrl *ctrl)
{
	bool	ret;

	pthread_mutex_lock(&(ctrl->lock_death.mutex));
	ret = ctrl->death;
	pthread_mutex_unlock(&(ctrl->lock_death.mutex));
	return (ret);
}

/* returns true if all philosophers are sated. Otherwise returns false
 */
bool	check_sated(t_ctrl *ctrl)
{
	bool	ret;

	pthread_mutex_lock(&(ctrl->lock_sated.mutex));
	ret = ctrl->nu_sated == ctrl->nu_philo;
	pthread_mutex_unlock(&(ctrl->lock_sated.mutex));
	return (ret);
}

/* returns the status of the philosopher, either EATING (when she's
 * currently eating) or OTHER (when she's involved in some other activity,
 * sleeping or thinking). This is important information for watcher, because
 * a philosopher can only die when she is not eating.
 */
bool	check_status(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&(philo->lock_status.mutex));
	ret = philo->status;
	pthread_mutex_unlock(&(philo->lock_status.mutex));
	return (ret);
}

/* returns the time in ms since the philosopher took her last meal
 */
t_ms	time_last_meal(t_philo *philo)
{
	t_ms	time;

	pthread_mutex_lock(&(philo->lock_meal.mutex));
	time = philo->last_meal;
	pthread_mutex_unlock(&(philo->lock_meal.mutex));
	return (time);
}
