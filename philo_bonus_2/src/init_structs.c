/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/12 18:41:20 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	**init_semaphores(t_ctrl *ctrl, t_err *error)
{
	sem_t	*ret;
	
	ret = ft_malloc(3 * sizeof(sem_t *))
	if (error)
		return (0);
	sem_unlink("/forks");
	sem[FORKS] = sem_open("/forks", O_CREAT, 0644, nu_philo);
	sem_unlink("/start");
	sem[START] = sem_open("/start", O_CREAT, 0644, 1);
	sem_unlink("/print");
	sem[PRINT] = sem_opne("/print", O_CREAT, 0644, 1);
	return (ret);
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
	return (ctrl);
}
	
