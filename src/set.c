/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:15:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/15 15:45:15 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Every shared parameter that is modified during simulation is protected with a
 * mutex of its own, so that no thread can check the value while another thread
 * is modifying it. (For example: when the main thread is busy setting 'death'
 * to true, the lock_death mutex is locked and threads wanting to check the
 * death parameter have to wait until the main thread has finished updating the
 * value).
 * 
 * All 'set_ / increment_' functions have their 'check' counterpart (see
 * check.c), where the same mutex is used. While the value is being changed,
 * threads who want to read the value have to wait until the writing thread
 * unlocks the corresponding mutex and vice versa.
 *
 * This mutex system avoids data races (which would cause undefined behaviour)
 */

void	set_death(t_ctrl *ctrl)
{
	pthread_mutex_lock(&(ctrl->lock_death.mutex));
	ctrl->death = true;
	pthread_mutex_unlock(&(ctrl->lock_death.mutex));
}

void	increment_sated(t_ctrl *ctrl)
{
	pthread_mutex_lock(&(ctrl->lock_sated.mutex));
	ctrl->nu_sated++;
	pthread_mutex_unlock(&(ctrl->lock_sated.mutex));
}

void	set_status(t_philo *philo, bool status)
{
	pthread_mutex_lock(&(philo->lock_status.mutex));
	philo->status = status;
	pthread_mutex_unlock(&(philo->lock_status.mutex));
}

void	set_last_meal(t_philo *philo, t_ms time)
{
	pthread_mutex_lock(&(philo->lock_meal.mutex));
	philo->last_meal = time;
	pthread_mutex_unlock(&(philo->lock_meal.mutex));
}

void	update_forks_in_use(t_philo *philo, int add)
{
	pthread_mutex_lock(&(philo->ctrl->lock_forks_in_use.mutex));
	philo->ctrl->forks_in_use += add;
	pthread_mutex_unlock(&(philo->ctrl->lock_forks_in_use.mutex));
}

