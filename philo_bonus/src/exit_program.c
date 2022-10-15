/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:55:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 00:39:04 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* closes a semaphore and unlinks it
 */
void	close_sem(sem_t *semaphore)
{
	if (semaphore != SEM_FAILED)
		sem_close(semaphore);
}

/* closes semaphores 
 */
void	close_all_semaphores(t_ctrl *ctrl)
{
	close_sem(ctrl->print_sem);
	close_sem(ctrl->forks);
	close_sem(ctrl->last_meal_sem);
	close_sem(ctrl->sated);
	close_sem(ctrl->stop_all);
}

/* frees all allocated memory in ctrl struct
 */
void	free_ctrl(t_ctrl *ctrl)
{
	close_all_semaphores(ctrl);
	free(ctrl->cpids);
	free(ctrl);
}

/* once all child processes are running, semaphores can be unlinked safely
 */
void	unlink_all_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/print_sem");
	sem_unlink("/last_meal_sem");
	sem_unlink("/sated");
	sem_unlink("/all_sated");
	sem_unlink("/stop_all");
}

/* exits the program in a clean way. First, an error message is printed.
 * Depending on the stage of the program where the error occurred,
 * resources are freed, any remaining child processes are terminated and
 * semaphores are closed and unlinked.
 * If a system error occurred, program exits with EXIT_FAILURE (1).
 * If a user error occurre, program exits with EXIT_USER_ERROR (2).
 * If no error occured, program exits with EXIT_SUCCESS (0).
 */
void	exit_program(t_ctrl *ctrl, t_err *error)
{
	if (*error)
		printf("%s %s\n", PHILO, *error);
	if (ctrl == NULL)
		exit(EXIT_FAILURE);
	if (!my_strcmp(*error, INV_TIME) || !my_strcmp(*error, INV_PH)
		|| !my_strcmp(*error, INV_ME) || !my_strcmp(*error, START_SATED)
		|| !my_strcmp(*error, NO_PH))
	{
		free(ctrl);
		exit(EXIT_USER_ERROR);
	}
	if (!my_strcmp(*error, FORK_ERR))
		kill_all(ctrl, error);
	free_ctrl(ctrl);
	unlink_all_semaphores();
	if (*error)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
