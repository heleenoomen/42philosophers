/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 10:54:34 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/08 13:55:53 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	nu_philo;

	if (*error)
		return ;
	nu_philo = ctrl->nu_philo;
	i = -1;
	while (++i < nu_philo)
	{
		ctrl->philos[i].nbr = i + 1;
		ctrl->philos[i].controller = ctrl;
		ctrl->philos[i].meals = 0;
		get_forks(ctrl->philos + i);
		ctrl->philos[i].sated = false;
		ctrl->philos[i].free = true;
	}
}

