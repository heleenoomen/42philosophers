/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:22:58 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/15 15:32:14 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo)
{
	if (philo->nbr % 2)
	{
		philo->left = philo->ctrl->forks + ((philo->nbr - 1) % philo->ctrl->nu_philo);
		philo->right = philo->ctrl->forks + (philo->nbr % philo->ctrl->nu_philo);
	}
	else
	{
		philo->right = philo->ctrl->forks + ((philo->nbr - 1) % philo->ctrl->nu_philo);
		philo->left = philo->ctrl->forks + (philo->nbr % philo->ctrl->nu_philo);
	}
}

