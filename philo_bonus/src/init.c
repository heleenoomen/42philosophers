/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/17 14:17:14 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*init_semaphore(char *name, int value, t_err *error)
{
	sem_t	*ret;

	sem_unlink(name);
	ret = sem_open(name, O_CREAT, 0664, value);
	if (ret == SEM_FAILED)
	{
		perror(name);
		*error = SEM_ERR; 
	}
	return (ret);
}
		
void	init_all_semaphores(t_ctrl *ctrl, t_err *error)
{
	if (*error)
		return ;
	ctrl->forks = init_semaphore("forks", ctrl->nu_philo, error);
	ctrl->print = init_semaphore("print", 1, error);
	ctrl->last_meal_sem = init_semaphore("last_meal_sem", 1, error);
	ctrl->status_sem = init_semaphore("status_sem", 1, error);
	ctrl->died_sem = init_semaphore("died_sem", 1, error);
}

t_ctrl	*init_ctrl(int argc, char **argv, t_err *error)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *) ft_malloc(sizeof(t_ctrl), error);
	if (*error)
		return (NULL);
	ctrl->nu_philo = ft_atoi(argv[1], error, PH);
	ctrl->time_die = ft_atoi(argv[2], error, TI);
	ctrl->time_eat = ft_atoi(argv[3], error, TI);
	ctrl->time_sleep = ft_atoi(argv[4], error, TI);
	if (argc == 6)
		ctrl->max_meals = ft_atoi(argv[5], error, ME);
	else
		ctrl->max_meals = -1;
	if (*error == NULL && ctrl->nu_philo == 0)
		*error = NO_PH;
	if (*error)
		return (ctrl);
	init_all_semaphores(ctrl, error);
	ctrl->status = NOT_EATING;
	ctrl->meals = 0;
	ctrl->died = false;
	ctrl->cpids = ft_calloc(ctrl->nu_philo * sizeof(int), error);
	return (ctrl);
}
	
