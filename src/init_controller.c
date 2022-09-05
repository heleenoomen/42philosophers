/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/05 13:13:15 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ctrl	*init_controller(int argc, char **argv, t_err *error)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *) ft_malloc(sizeof(t_ctrl), error);
	if (error)
		return (NULL);
	ctrl->nu_philo = ft_atoui(argv[1], error, PH);
	ctrl->time_die = ft_atoui(argv[2], error, TI);
	ctrl->time_eat = ft_atoui(argv[3], error, TI);
	ctrl->time_sleep = ft_atoui(argv[4], error, TI);
	if (argc == 6)
		ctrl->max_meals = ft_atoui(argv[5], error, ME);
	else
		ctrl->max_meals = -1;
	if (error)
		return (ctrl);
	ctrl->threads = ft_malloc(ctrl->nu_philo * sizeof(pthread_t), error);
	ctrl->forks = ft_malloc(ctrl->nu_philo * sizeof(pthread_mutex_t), error);
	ctrl->philos = ft_malloc(ctrl->nu_philo * sizeof(t_philo), error);
	if (error)
		return (ctrl);
	init_forks(ctrl, error);
	if (error)
		return (ctrl);
	init_philos(ctrl);
	int i = 0;
	while (i < ctrl->nu_philo)
	{
		printf("ctrl->nu_philo[i].nbr = %i\n", ctrl->philos[i].nbr);
		i++;
	}
	return (ctrl);
}
	
