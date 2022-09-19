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
	sem_wait(ctrl->print);
	ctrl->last_action = gettime();
	if (!(ctrl->died) || !ft_strcmp(action, DIE))
		printf("%u %i %s\n", ctrl->last_action - ctrl->start, ctrl->index, action);
	sem_post(ctrl->print);
}
	
void	ph_eat(t_ctrl *ctrl)
{
	t_ms	start_meal;

	sem_wait(ctrl->forks);
	print_action(ctrl, FORK);
	sem_wait(ctrl->forks);
	start_meal = gettime();
	print_action(ctrl, FORK);
	print_action(ctrl, EAT);
	set_status(ctrl, EATING);
	set_last_meal(ctrl, ctrl->last_action);
	ctrl->last_action = start_meal;
	ph_usleep(ctrl, ctrl->time_eat);	
	sem_post(ctrl->forks);
	sem_post(ctrl->forks);
	set_status(ctrl, NOT_EATING);
	ctrl->meals++;
	if (ctrl->meals == ctrl->max_meals)
	{
		pthread_detach(ctrl->watcher);
		sem_post(ctrl->status_sem);
		sem_post(ctrl->died_sem);
		sem_post(ctrl->last_meal_sem);
		exit(SATED);
	}
}

void	ph_sleep(t_ctrl *ctrl)
{
	print_action(ctrl, SLEEP);
	ph_usleep(ctrl, ctrl->time_sleep);
}

