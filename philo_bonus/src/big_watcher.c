/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_watcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:01:17 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/17 14:24:40 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	death_or_error(t_ctrl *ctrl, int status, t_err *error)
{
	int	i;

	i = -1;
	while (++i < ctrl->nu_philo)
	{
		kill(ctrl->cpids[i], SIGKILL);
		ctrl->cpids[i] = 0;
	}	
	if (status != DEATH)
		*error = UNDEF_CHILD_PROC;
	return ;
}

bool	check_lonely(t_ctrl *ctrl)
{
	int	start;

	if (ctrl->nu_philo > 1)
		return (false);
	start = gettime();
	while (gettime() < start + ctrl->time_die)
		usleep(500);
	kill(ctrl->cpids[0], SIGKILL);	
	printf("%u 1 died\n", gettime() - ctrl->start);
	return (true);
}

void	big_watcher(t_ctrl *ctrl, t_err *error)
{
	int	status;
	int	sated;

	sated = 0;
	if (check_lonely(ctrl))
		return ;
	while (1)
	{
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
			{
				status = WEXITSTATUS(status);
				if (status != SATED)
					return (death_or_error(ctrl, status, error));
				else
				{
					sated++;
					if (sated == ctrl->nu_philo)
						return ;
				}
			}
	}
}

