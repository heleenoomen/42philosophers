/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/16 16:01:36 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*init_semaphore(char *name, int value, t_err *error)
{
	sem_t	*ret;

	sem_unlink(name);
	ret = sem_open(name, O_CREAT, 0664, value);
	if (ret == SEM_FAILED)
		*error = SEM_ERR; 
	return (ret);
}
		
void	init_all_semaphores(t_ctrl *ctrl, t_err *error)
{
	if (*error)
		return ;
	ctrl->forks = init_semaphore("/tmp/forks", ctrl->nu_philo);
	ctrl->print = init_semaphore("/tmp/print", 1);
	ctrl->last_meal_sem = init_semaphore("/tmp/last_meal_sem", 1);
	ctrl->status_sem = init_semaphore("/tmp/status_sem", 1);
	ctrl->died_sem = init_semaphore("/tmp/died_sem", 1);
}

t_ctrl	*init_ctrl(int argc, char **argv, t_err *error)
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
	init_all_semaphores(ctrl, error);
	ctrl->status = NOT_EATING;
	ctrl->meals = 0;
	ctrl->died = false;
	return (ctrl);
}
	
