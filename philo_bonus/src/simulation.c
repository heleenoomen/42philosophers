/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:45:13 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 17:08:03 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	run_philosophers(t_philo *philo)
{
	philo->last_meal = ctrl->start;
	while (philo->ctrl->death == false)
	{
		ph_eat(philo);
		ph_sleep(philo);
		print_action(philo, THINK, gettime());
	}
	exit (0);
}
	
void	wait_for_child_processes(t_ctrl *ctrl, int nu_created)
{
	int	 i;

	i = -1;
	while (++i < nu_created)
		waitpid(ctrl->cpids[i], NULL, WIFEXITED);
}

void	start_simulation(t_ctrl *ctrl)
{
	int	i;

	i = -1;
	while (++i < ctrl->nu_philo)
	{
		ctrl->cpids[i] = fork();
		if (ctrl->cpids[i] == -1)
			break ;
		if (ctrl->cpids[i] == 0)
			run_philosophers(ctrl->philos + i);
	}
	wait_for_child_processes(ctrl->cpids, i);
}
