/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saturation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:01:17 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/15 13:14:32 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* If max_meals parameter was not entered by user (and set to -1 during intia-
 * lization), saturation_watcher has nothing to do and returns immediately.
 * Otherwise, he waits until all philosophers have posted on the sated
 * semaphore, upon which he posts on the stop_all semaphore to wake up all
 * watcher2 threads throughout processes, which whill make all threads return
 * and all child processes exit. Finally, all_sated is posted upon to make
 * threads that where hanging after saturation resume (i.e. join 
 * watchers and exit).
 */
void	saturation_watcher(t_ctrl *ctrl)
{
	int	i;

	if (ctrl->max_meals == -1)
		return ;
	i = -1;
	while (++i < ctrl->nu_philo)
		sem_wait(ctrl->sated);
	sem_post(ctrl->stop_all);
	sem_post(ctrl->all_sated);
}
