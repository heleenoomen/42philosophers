/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 10:44:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/04 19:09:45 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_ctrl *ctrl, char *error)
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
			error = MUTEX_ERR;
			return ;
		}
		ctrl->forks[i].init = true;
		ctrl->forks[i].locked = false;
		i++;
	}
	if (pthread_mutex_init(&(ctrl->print_lock.mutex), NULL))
	{
		ctrl->print_lock.init = false;
		error = MUTEX_ERR;
		return ;
	}
	ctrl->print_lock.init = true;
	ctrl->print_lock.locked = false;
}

void	get_forks(t_philo *philo)
{
	if (philo->nbr % 2)
	{
		philo->one = philo->controller->forks + philo->nbr - 1;
		if (philo->nbr == philo->controller->nu_philo)
			philo->two = philo->controller->forks;
		else
			philo->two = philo->controller->forks + philo->nbr;
	}
	else
	{
		if (philo->nbr == philo->controller->nu_philo)
			philo->one = philo->controller->forks;
		else
			philo->one = philo->controller->forks + philo->nbr;
		philo->two = philo->controller->forks + philo->nbr - 1;
	}
}	

void	take_forks(t_philo *philo)
{
	t_ms	time;

	pthread_mutex_lock(&(philo->one->mutex));
	time = gettime();
	philo->one->locked = true;
	print_action(philo, FORK, time);
	philo->last_action = time;
	if (philo_die(philo) || philo->controller->death)
	{
		pthread_mutex_unlock(&(philo->two->mutex));
		return ;
	}
	pthread_mutex_lock(&(philo->two->mutex));
	time = gettime();
	philo->two->locked = true;	
	philo->last_action = time;
	print_action(philo, FORK, time);
}

void	leave_forks(t_philo *philo)
{
	if (!philo->has_forks)
		return ;
	pthread_mutex_unlock(&(philo->two->mutex));
	philo->two->locked = false;
	pthread_mutex_unlock(&(philo->one->mutex));
	philo->one->locked = false;
}
	
