/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:38:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/13 13:43:32 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_action(t_ctrl *ctrl, t_ms time, char *action)
{
	sem_wait(ctrl->print);
	if (!(ctrl->died) || !ft_strcmp(action, DIE))
		printf("%u %i %s\n", time, ctrl->index, action);
	sem_post(ctrl->print);
}
	
void	ph_eat(t_ctrl *ctrl)
{
	sem_wait(ctrl->forks);
	print_action(ctrl, gettime() - ctrl->start, FORK);
	sem_wait(ctrl->forks);
	sem_wait(ctrl->last_meal_sem);
	ctrl->last_meal = gettime();
	sem_post(ctrl->last_meal_sem);
	sem_wait(ctrl->status_sem);
	ctrl->status = EATING;
	sem_post(ctrl->status_sem);
	print_action(ctrl, ctrl->last_meal - ctrl->start, FORK);
	print_action(ctrl, ctrl->last_meal - ctrl->start, EAT);
	ph_usleep(ctrl, ctrl->time_eat - (gettime() - ctrl->last_meal));	
	sem_post(ctrl->forks);
	sem_post(ctrl->forks);
	ctrl->status = NOT_EATING;
	ctrl->meals++;
	if (ctrl->meals == ctrl->max_meals)
	{
		exit (SATED);
	}
}

void	ph_sleep(t_ctrl *ctrl)
{
	t_ms	sleep;

	sleep = gettime();
	print_action(ctrl, sleep - ctrl->start, SLEEP);
	ph_usleep(ctrl, ctrl->time_sleep - (gettime() - sleep));
}

