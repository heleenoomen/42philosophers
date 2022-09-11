/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:48:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 09:52:33 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

