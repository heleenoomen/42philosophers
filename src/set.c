/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:15:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 09:55:38 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

