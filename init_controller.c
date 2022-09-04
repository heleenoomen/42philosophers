/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/04 12:34:11 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ctrl	*init_controller(int argc, char **argv, char *error)
{
	t_ctrl	*ctrl;

	ctrl = ft_malloc(sizeof(t_ctrl), error);
	if (error)
		return (NULL);
	ctrl->nu_philo = ft_atoui(argc[1], error, PH);
	ctrl->time_die = ft_atoui(argc[2], error, TI);
	ctrl->time_eat = ft_atoui(argc[3], error, TI);
	ctrl->time_sleep = ft_atoui(argc[4], error, TI);
	if (argc == 6)
		ctrl->max_meals = ft_atoui(argc[5], error, ME);
	else
		ctrl->max_meals = -1;
	if (error)
		return (ctrl);
	ctrl->threads = ft_malloc(ctrl->nu_philo * sizeof(pthread_t), error);
	ctrl->forks = ft_malloc(ctrl->nu_philo * sizeof(pthread_mutex_t), error);
	ctrl->philos = ft_malloc(ctrl->nu_philo * sizeof(t_philo));
	if (error)
		return (ctrl);
	init_forks(ctrl, error);
	if (error)
		return (ctrl);
	init_philos(ctrl, error);
	return (ctrl);
}
	
