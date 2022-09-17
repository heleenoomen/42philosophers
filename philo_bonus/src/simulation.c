/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/17 15:40:24 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	run_philosophers(t_ctrl *ctrl)
{
	ctrl->status = NOT_EATING;
	while (check_died(ctrl) == false)
	{
		ph_eat(ctrl);
		ph_sleep(ctrl);
		print_action(ctrl, gettime() - ctrl->start, THINK);
	}
	free(ctrl);
	pthread_detach(ctrl->watcher);
	printf("my last meal was at %u\n", ctrl->last_meal - ctrl->start);
	exit(DEATH);
}


void	watcher(t_ctrl *ctrl)
{
	t_ms	last_meal;
	while (1)
	{
		last_meal = time_last_meal(ctrl);

		if (check_status(ctrl) == NOT_EATING && ((gettime() - last_meal)
				> ctrl->time_die))
		{
			set_died(ctrl);
			sem_wait(ctrl->print);
			printf("%u %i died\n", gettime() - ctrl->start, ctrl->index);
			printf("last meal started at: %u, actual time = %u\n", ctrl->last_meal - ctrl->start, gettime() - ctrl->start);
			printf("time since last meal = %u\n", gettime() - ctrl->last_meal);
			printf("last_meal = %u\n", last_meal);
			exit(DEATH);
		}
	}
}

int	ft_fork(t_err *error)
{
	int	ret;

	ret = fork();
	if (ret == -1)
		*error = FORK;
	return (ret);
}

void	start_simulation(t_ctrl *ctrl, t_err *error)
{
	int	i;

	i = -1;
	ctrl->start = gettime();
	ctrl->last_meal = ctrl->start;
	while (++i < ctrl->nu_philo)
	{
		ctrl->cpids[i] = ft_fork(error);
		if (*error)
			exit_program(ctrl, error); 
		if (ctrl->cpids[i] == 0)
		{
			ctrl->index = i + 1;
			if (pthread_create(&(ctrl->watcher), NULL, (void *) &watcher, (void *)ctrl))
				exit_program (ctrl, error);
			run_philosophers(ctrl);
		}
	}
	big_watcher(ctrl, error);
}

