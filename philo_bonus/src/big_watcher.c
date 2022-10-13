/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_watcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:01:17 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 11:13:56 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	death_or_error(t_ctrl *ctrl, int status, t_err *error)
{
	int	i;

	i = -1;
	while (++i < ctrl->nu_philo)
	{
		kill(ctrl->cpids[i], SIGTERM);
		ctrl->cpids[i] = 0;
	}	
	if (status != DEATH)
	{
		if (status == THREAD_ERR_CHILD)
			*error = THREAD_ERR;
		else
			*error = UNDEF_CHILD_PROC;
	}
	exit_program(ctrl, error);
}

/* if the number of philosophers is bigger than 1, returns to big watcher
 * without doing anything (i.e. big watcher will continue to go into its normal
 * routine). Else, the lonely philosopher is allowed to live for time_die
 * millisecond. She will take the sole fork and will fruitlessly wait for a
 * second fork until check_lonely kills her, prints the death message and
 * exits the program.
 */
void	check_lonely(t_ctrl *ctrl, t_err *error)
{
	int	start;

	if (ctrl->nu_philo > 1)
		return ;
	start = gettime();
	while (gettime() < start + ctrl->time_die)
		usleep(500);
	kill(ctrl->cpids[0], SIGTERM);
	printf("%u 1 died\n", gettime() - ctrl->start);
	exit_program(ctrl, error);
}

/* this is the main process after creating all child processes (i.e. after
 * spawning the philosophers). Big_watcher will check constantly if a child
 * process has exited. If a child process has exited with SATED status, the
 * other philosophers (child processes) are allowed to continue running until
 * they become sated as well.
 * If, on the contrary, a child process has exited with any other status,
 * error_or_death is called to terminate all other processes and exit the
 * program.
 * Before doing anything, the big watcher checks if there is only one philo-
 * pher, in which case a special routine is carried out before exiting.
 */
void	big_watcher(t_ctrl *ctrl, t_err *error)
{
	int	status;
	int	sated;

	sated = 0;
	check_lonely(ctrl, error);
	while (1)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			if (status != SATED)
				death_or_error(ctrl, status, error);
			else
			{
				sated++;
				if (sated == ctrl->nu_philo)
					exit_program(ctrl, error);
			}
		}
	}
}
