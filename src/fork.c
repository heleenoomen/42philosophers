/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 10:44:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/07 20:13:40 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	nu_forks;

	i = 0;
	nu_forks = ctrl->nu_philo;
	while (i < nu_forks)
	{
		if (pthread_mutex_init(&(ctrl->forks[i].mutex), NULL))	
		{
			ctrl->forks[i].init = false;
			*error = MUTEX_ERR;
			return ;
		}
		ctrl->forks[i].init = true;
		ctrl->forks[i].locked = false;
		i++;
	}
	if (pthread_mutex_init(&(ctrl->print_lock.mutex), NULL))
	{
		ctrl->print_lock.init = false;
		*error = MUTEX_ERR;
		return ;
	}
	ctrl->print_lock.init = true;
	ctrl->print_lock.locked = false;
	ctrl->print_queue = 0;
}

void	get_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = (philo->nbr - 1) % philo->controller->nu_philo;
	right = philo->nbr % philo->controller->nu_philo;
	if (philo->nbr % 2)
	{
		philo->one = philo->controller->forks + left;
		philo->two = philo->controller->forks + right;
	}
	else
	{
		philo->one = philo->controller->forks + right;
		philo->two = philo->controller->forks + left;
	}
}

