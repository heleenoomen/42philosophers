/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 10:54:34 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 10:42:34 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* if error happens to be already set, nothing is initialized and the function
 * returns. The philos array (the struct each philosopher is going to carry
 * along as a parameter to their routine) is filled in. Each philosophers number
 * is their index in the array plus 1 (so, ctrl->philos[0] belongs to philospher
 * nbr one, etc.). Each philosopher gets a pointer to the controller struct in
 * order to access shared parameters (time_eat, time_sleep) and the shared
 * print_lock mutex. Meals is set to zero and sated is set to false, since no
 * philosopher has eaten before the simulation starts. get_forks is called to
 * give every philosopher a left and a right fork in the ctrl->forks array, and
 * decide which fork they should take first (philo->one) and which second
 * (philo->two). Free is set to false, since no philosopher is can die before the
 * simulation starts.
 */
void	init_philos(t_ctrl *ctrl, t_err *error)
{
	int	i;
	int	nu_philo;

	if (*error)
		return ;
	nu_philo = ctrl->nu_philo;
	i = -1;
	while (++i < nu_philo)
	{
		ctrl->philos[i].nbr = i + 1;
		ctrl->philos[i].ctrl = ctrl;
		ctrl->philos[i].meals = 0;
		ctrl->philos[i].left = ctrl->forks + ((i) % nu_philo);
		ctrl->philos[i].right = ctrl->forks + ((i + 1) % nu_philo);
		init_mutex(&(ctrl->philos[i].lock_meal), error);
		init_mutex(&(ctrl->philos[i].lock_status), error);
		ctrl->philos[i].status = EATS;
	}
}

