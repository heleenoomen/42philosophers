/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/19 17:19:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_ctrl *ctrl, char *action)
{
	if (check_died(ctrl))
		return ;
	sem_wait(ctrl->print);
	ctrl->last_action = gettime();
	printf("%u %i %s\n", ctrl->last_action - ctrl->start, ctrl->index, action);
	sem_post(ctrl->print);
}

void	take_forks(t_ctrl *ctrl)
{
	sem_wait(ctrl->forks);
	print_action(ctrl, FORK);
	sem_wait(ctrl->forks);
	print_action(ctrl, FORK);
}

void	leave_forks(t_ctrl *ctrl)
{
	sem_post(ctrl->forks);
	sem_post(ctrl->forks);
}
	
void	ph_eat(t_ctrl *ctrl)
{
	bool	sated;

	take_forks(ctrl);
	print_action(ctrl, EAT);
	set_status(ctrl, EATING);
	set_last_meal(ctrl, ctrl->last_action);
	sated = ++ctrl->meals == ctrl->max_meals;
	ph_usleep(ctrl, ctrl->time_eat);
	leave_forks(ctrl);
	if (sated)
	{
		set_sated(ctrl);
		pthread_join(ctrl->watcher, NULL);
		exit(SATED);
	}
}

void	ph_sleep(t_ctrl *ctrl)
{
	print_action(ctrl, SLEEP);
	set_status(ctrl, OTHER);
	ph_usleep(ctrl, ctrl->time_sleep);
}

