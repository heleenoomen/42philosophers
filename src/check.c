/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:48:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/15 15:49:05 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* every shared parameter that is modified during simulation is protected with a
 * mutex of its own, so that no thread can check the value while another thread
 * is modifying it. (For example: when the main thread is busy setting 'death'
 * to true, the lock_death mutex is locked and threads wanting to check the
 * death parameter have to wait until the main thread has finished updating the
 * value).
 */
bool	check_death(t_ctrl *ctrl)
{
	bool	ret;

	pthread_mutex_lock(&(ctrl->lock_death.mutex));
	ret = ctrl->death;
	pthread_mutex_unlock(&(ctrl->lock_death.mutex));
	return (ret);
}

bool	check_sated(t_ctrl *ctrl)
{
	bool	ret;

	pthread_mutex_lock(&(ctrl->lock_sated.mutex));
	ret = ctrl->nu_sated == ctrl->nu_philo;
	pthread_mutex_unlock(&(ctrl->lock_sated.mutex));
	return (ret);
}

bool	check_status(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&(philo->lock_status.mutex));
	ret = philo->status;
	pthread_mutex_unlock(&(philo->lock_status.mutex));
	return (ret);
}

t_ms	time_last_meal(t_philo *philo)
{
	t_ms	time;

	pthread_mutex_lock(&(philo->lock_meal.mutex));
	time = philo->last_meal;
	pthread_mutex_unlock(&(philo->lock_meal.mutex));
	return (time);
}

bool	check_forks_in_use(t_philo *philo)
{
	int	forks_in_use;

	pthread_mutex_lock(&(philo->ctrl->lock_forks_in_use.mutex));
	forks_in_use = philo->ctrl->forks_in_use;
	pthread_mutex_unlock(&(philo->ctrl->lock_forks_in_use.mutex));
	return (forks_in_use < 4);
}
