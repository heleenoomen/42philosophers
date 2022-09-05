/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 10:54:34 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/05 09:55:19 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_ctrl *ctrl)
{
	int	i;
	int	nu_philo;

	nu_philo = ctrl->nu_philo;
	i = -1;
	while (++i < nu_philo)
	{
		ctrl->philos[i].nbr = i + 1;
		ctrl->philos[i].controller = ctrl;
		ctrl->philos[i].meals = 0;
		ctrl->philos[i].last_action = 0;
		ctrl->philos[i].last_meal = 0;
		if (ctrl->max_meals != -1)
			ctrl->philos[i].meals = 0;
		else
			ctrl->philos[i].meals = -1;
		ctrl->philos[i].has_forks = false;
		ctrl->philos[i].died = false;
	}
}

