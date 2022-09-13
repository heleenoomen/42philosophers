/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/13 13:30:29 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_ctrl *ctrl, t_err *error)
{
	if (*error)
		return ;
	sem_unlink("/tmp/forks");
	ctrl->forks = sem_open("/tmp/forks", O_CREAT, 0664, ctrl->nu_philo);
	if (ctrl->forks == SEM_FAILED)
		perror("forks not created");
	printf("%i forks are created\n", ctrl->nu_philo);
	sem_unlink("/tmp/print");
	ctrl->print = sem_open("/tmp/print", O_CREAT, 0664, 1);
	if (ctrl->forks == SEM_FAILED)
		perror("print not created");
	sem_unlink("/tmp/status_sem");
	ctrl->status_sem = sem_open("/tmp/status_sem", O_CREAT, 0664, 1);
	sem_unlink("/tmp/died_sem");
	ctrl->died_sem = sem_open("/tmp/died_sem", O_CREAT, 0664, 1);
	sem_unlink("/tmp/last_meal_sem");
	ctrl->last_meal_sem = sem_open("/tmp/last_meal_sem", O_CREAT, 0664, 1);
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
	init_semaphores(ctrl, error);
	ctrl->status = NOT_EATING;
	ctrl->meals = 0;
	ctrl->died = false;
	return (ctrl);
}
	
