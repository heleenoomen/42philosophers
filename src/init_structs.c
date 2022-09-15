/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/11 14:20:02 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* at the start of the simulation, no one has died yet and no one is sated
 * unless the user entered 0 for the max_meals parameter, in which case everyone
 * is sated at the start and the simulation will end almost immediately.
 */
void	ctrl_init_flags_counters(t_ctrl *ctrl)
{
	ctrl->death = false;
	if (ctrl->max_meals == 0)
		ctrl->nu_sated = ctrl->nu_philo;
	else
		ctrl->nu_sated = 0;
}

/* give each entry in the ctrl->philos array their parameters and initialize
 * their mutexes
 * 'status' is set to EATING to prevent main from declaring the philosopher death
 * before it had the chance to fill in its start time
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
		ctrl->philos[i].status = EATING;
	}
}

/* allocate space for ctrl struct, parse user parameters, allocate space for
 * arrays and initialize mutexes and the philos array.
 */
t_ctrl	*init_controller(int argc, char **argv, t_err *error)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *) ft_malloc(sizeof(t_ctrl), error);
	if (*error)
		return (NULL);
	ctrl->nu_philo = ft_atoui(argv[1], error, PH);
	ctrl->time_die = ft_atoui(argv[2], error, TI);
	ctrl->time_eat = ft_atoui(argv[3], error, TI);
	ctrl->time_sleep = ft_atoui(argv[4], error, TI);
	if (argc == 6)
		ctrl->max_meals = ft_atoui(argv[5], error, ME);
	else
		ctrl->max_meals = -1;
	if (*error)
		return (ctrl);
	ctrl->threads = ft_malloc(ctrl->nu_philo * sizeof(pthread_t), error);
	ctrl->forks = ft_malloc(ctrl->nu_philo * sizeof(t_mutex), error);
	ctrl->philos = ft_malloc(ctrl->nu_philo * sizeof(t_philo), error);
	init_all_mutexes(ctrl, error);
	init_philos(ctrl, error);
	ctrl_init_flags_counters(ctrl);
	return (ctrl);
}
	
