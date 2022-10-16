/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:55:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 13:40:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* destroys a mutex in case it was initialized successfully
 */
void	destroy_mutex(t_mutex *mutex)
{
	if (mutex->init)
		pthread_mutex_destroy(&(mutex->mutex));
}

/* if the forks array is not NULL, all forks that were initialized are
 * destroyed. If the philos array is not NULL, all mutexes in all philo-structs
 * that were initialized are destroyed. Finally, the four remaining mutexes in
 * the ctrl are destroyed if they were successfully initialized
 */
void	destroy_all_mutexes(t_ctrl *ctrl)
{
	int		i;

	if (ctrl->forks != NULL)
	{
		i = -1;
		while (++i < ctrl->nu_philo)
			destroy_mutex(ctrl->forks + i);
	}
	if (ctrl->philos != NULL)
	{
		i = -1;
		while (++i < ctrl->nu_philo)
		{
			destroy_mutex(&(ctrl->philos[i].lock_meal));
			destroy_mutex(&(ctrl->philos[i].lock_status));
		}
	}
	destroy_mutex(&(ctrl->lock_death));
	destroy_mutex(&(ctrl->lock_sated));
	destroy_mutex(&(ctrl->lock_print));
}

/* prints error message in case error was set. Frees all resources that were
 * allocated based on the phase of the program where the error occurred.
 * Returns 0 in case there was no error.
 * Returns 1 in case of a system error (malloc, thread creation or mutex
 * initialization failed).
 * Returns 2 in case the user entered invalid parameters.
 */
int	exit_program(t_ctrl *ctrl, t_err *error)
{
	if (!my_strcmp(INV_PH, *error) || !my_strcmp(INV_TIME, *error)
		|| !my_strcmp(INV_ME, *error) || !my_strcmp(NO_PH, *error)
		|| !my_strcmp(START_SATED, *error))
	{
		printf("%s%s %s\n%s", GREEN_BOLD, PHILO, *error, RESET_COLOR);
		free(ctrl);
		return (2);
	}
	if (*error)
		printf("%s %s\n", PHILO, *error);
	if (ctrl == NULL)
		return (1);
	destroy_all_mutexes(ctrl);
	free(ctrl->threads);
	free(ctrl->forks);
	free(ctrl->philos);
	free(ctrl);
	if (*error)
		return (1);
	return (0);
}
