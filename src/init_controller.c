/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/10 17:35:01 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_flags_counters_controller(t_ctrl *controller)
{
	controller->death = false;
	controller->nu_sated = 0;
}

t_ctrl	*init_controller(int argc, char **argv, t_err *error)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *) ft_malloc(sizeof(t_ctrl), error);
	if (*error)
		return (NULL);
	ctrl->nu_philo = ft_atoui(argv[1], error, PH);
	ctrl->time_die = ft_atoui(argv[2], error, TI);
	ctrl->time_eat = ft_atoui(argv[3], error, TI);
	ctrl->time_sleep = ft_atoui(argv[4], error, TI);
	if (argc == 6)
		ctrl->max_meals = ft_atoui(argv[5], error, ME);
	else
		ctrl->max_meals = -1;
	if (*error)
		return (ctrl);
	ctrl->threads = ft_malloc(ctrl->nu_philo * sizeof(pthread_t), error);
	ctrl->mutexes = ft_malloc(ctrl->nu_philo * sizeof(t_mutex), error);
	ctrl->philos = ft_malloc(ctrl->nu_philo * sizeof(t_philo), error);
	init_forks(ctrl, error);
	init_philos(ctrl, error);
	init_flags_counters_controller(ctrl);
	return (ctrl);
}
	
