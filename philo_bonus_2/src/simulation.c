/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:05:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/12 19:30:51 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_philosophers(t_ctrl *ctrl)
{

	/* wait for start */
	sem_wait("/start");
	ctrl->start = gettime();
	ctrl->last_meal = start;
	ctrl->status = NOT_EATING;
	sem_post("/watcher");
	if (ctrl->nbr % 2)
		ph_usleep(philo, ctrl->time_eat - 10);
	while (check_died(ctrl))
	{
		ph_eat(philo);
		ph_sleep(philo);
		print_action(philo, THINK, gettime());
	}
	exit(DIED);
}

void	watcher(t_ctrl *ctrl)
{
	/* wait for start */
	sem_post("/watcher ready");
	sem_wait("/start");
	while (1)
	{
		if (check_died(ctrl))
		{
			set_died(ctrl);
			print_action(gettime(), ctrl->index, DIED);
			return ;
		}
		ph_usleep(200);
	}
}

int	ft_fork(t_ctrl *ctrl, int nu_forks, t_err *error)
{
	int	ret;

	ret = fork();
	if (ret == -1)
	{
		*error = FORK;
		exit_program(ctrl, nu_forks - 1, error);
	}
	return (ret);
}
		
void	child_process(t_ctrl *ctrl)
{
	if (pthread_create(&(ctrl->watcher), NULL, &watch, (void *)ctrl))
		exit (-1);
	run_philosophers(ctrl);
}

void	helper(t_ctrl *ctrl)
{
	int	i;
	int	status;
	int	sated;

	while (1)
	{
		i = -1;
		sated = 0;
		while (++i < ctrl->nu_philo)
		{
			waitpid(ctrl->cpids[1], &status, NULL);
			if (WIFEXITED(status) == DIED)
			{
				i = -1;
				while (++i < ctrl->nu_philo)
					kill(ctrl->cpids[1], SIGTERM);
				return ;		
			}	
			if (WIFEXITED(status) == SATED)
				sated++;
		}	
		if (sated == ctrl->nu_philo)
			return ;
	}
}

void	start_simulation(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	*cpids;

	cpids = ft_malloc(ctrl->nu_philo * sizeof(int));
	i = -1;
	while (++i < ctrl->nu_philo)
	{
		cpids[i] = ft_fork(error);
		if (cpids[i] == 0)
		{
			ctrl->index = i + 1;
			child_process(ctrl);
		}
	}
	while (--i > -1)
		sem_wait("/children");
	while (++i > nu_philo)
		sem_post("/start");
	helper(ctrl);
}

