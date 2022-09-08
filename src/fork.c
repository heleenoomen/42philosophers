/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 10:44:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/08 13:54:46 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_fork(t_fork *fork, t_err *error)
{
	if (pthread_mutex_init(&(fork->mutex), NULL))
	{
		*error = MUTEX_ERR;
		fork->init = false;
		return (true);
	}
	fork->init = true;
	return (false);	
}

void	init_forks(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	nu_forks;

	if (*error)
		return ;
	i = -1;
	nu_forks = ctrl->nu_philo;
	while (++i < nu_forks)
	{
		if (init_fork(&(ctrl->forks[i]), error))	
			return ;
	}
	if (init_fork(&(ctrl->print_lock.mutex), error))
		return ;
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

