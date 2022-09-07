/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:55:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/07 13:00:18 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_ctrl *controller)
{
	t_fork	*forks;
	int		i;
	int		nu_philo;

	forks = controller->forks;
	i = 0;
	nu_philo = controller->nu_philo;
	while (i < nu_philo)
	{
		if (forks[i].init)
			pthread_mutex_destroy(&(forks[i].mutex));
		else
			break ;
		i++;
	}
}

int	exit_program(t_ctrl *controller, t_err *error)
{
	if (*error)
		printf("%s %s\n", ERR, *error);
	if (ft_strcmp(INV_PH, *error) || ft_strcmp(INV_TIME, *error)
			|| ft_strcmp(INV_ME, *error))
	{
		free(controller);
		return (1);
	}
	if (*error == NULL || ft_strcmp(MUTEX_ERR, *error))
		free(controller->philos);
	destroy_mutexes(controller);
	free(controller->threads);
	free(controller->forks);
	free(controller->philos);
	free(controller);
	return (2);
}

