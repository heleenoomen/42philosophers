/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:48:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/10 19:09:52 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	death(t_ctrl *ctrl, bool action)
{
	bool	ret;
	pthread_mutex_lock(&(ctrl->death.mutex));
	if (action == CHECK && ctrl->death == false)
	{
		pthread_mutex_unlock(ctrl->death.mutex);
		return (false);
	}
	else if (action == SET)
		ctrl->death = true;
	pthread_mutex_unlock(ctrl->death.mutex);
	return (true);
}

t_ms	meal(t_philo *philo, t_ms start_meal, bool flag, bool status)
{
	int	ret;

	pthread_mutex_lock(&(philo->lock_meal.mutex));
	if (flag == SET)
	{
		philo->last_meal = start_meal;
		pthread_mutex_lock(&(philo->lock_status.mutex));
		philo->status = status;
		pthread_mutex_unlock(&(philo->lock_status.mutex));
		pthread_mutex_unlock(&(philo->lock_meal.mutex));
		return (0);
	}
	ret = philo->last_meal;
	pthread_mutex_unlock(&(philo->lock_meal.mutex));
	return (ret);
}	

bool	status(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&(philo->lock_status.mutex));
	ret = philo->status;
	pthread_mutex_unlock(&(philo->lock_status.mutex));
	return (ret);
}

bool	sated(t_ctrl *ctrl, bool flag)
{
	bool	ret;

	pthread_mutex_lock(&(ctrl->lock_sated.mutex));
	if (flag == SET)
	{
		ctrl->sated++;
		pthread_mutex_unlock(&(ctrl->lock_sated.mutex));
		return (true);
	}
	ret = ctrl->nu_sated == ctrl->nu_philo;
	pthread_mutex_unlock(&(ctrl->lock_sated.mutex));
	return (ret);
}
