/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:15:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 16:25:20 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Every shared variable that is modified or checked by several threads is
 * protected by a mutex of its own to avoid dataraces.
 * (For example: when the main thread is busy setting 'death' to true, the 
 * lock_death mutex is locked and threads wanting to check the death parameter
 * have to wait until the main thread has finished updating the value).
 * All 'set_ / increment_' functions have their 'check' counterpart (see
 * get.c), where the same mutex is used. While the value is being changed,
 * threads who want to read the value have to wait until the writing thread
 * unlocks the corresponding mutex and vice versa.
 */

/* sets the death flag to true if death has occurred at the table
 */
void	set_death(t_ctrl *ctrl)
{
	pthread_mutex_lock(&(ctrl->lock_death.mutex));
	ctrl->death = true;
	pthread_mutex_unlock(&(ctrl->lock_death.mutex));
}

/* increments the number of sated philosophers by one
 */
void	increment_sated(t_ctrl *ctrl)
{
	pthread_mutex_lock(&(ctrl->lock_sated.mutex));
	ctrl->nu_sated++;
	pthread_mutex_unlock(&(ctrl->lock_sated.mutex));
}

/* sets the status of the philosopher to 'status' (either EATING if she is
 * eating and thus cannot die, or OTHER if she is thinking or sleeping and thus
 * may die)
 */
void	set_status(t_philo *philo, bool status)
{
	pthread_mutex_lock(&(philo->lock_status.mutex));
	philo->status = status;
	pthread_mutex_unlock(&(philo->lock_status.mutex));
}

/* sets the last_meal variable to the time when the philosopher started her
 * last meal
 */
void	set_last_meal(t_philo *philo, t_ms time)
{
	pthread_mutex_lock(&(philo->lock_meal.mutex));
	philo->last_meal = time;
	pthread_mutex_unlock(&(philo->lock_meal.mutex));
}
