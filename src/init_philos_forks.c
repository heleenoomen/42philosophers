/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:00:10 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/22 17:38:10 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philos(t_ph_parms *parms, pthread_t **philos)
{
	*philos = malloc(parms->num_philos * sizeof(t_pthread));
	if (*philos == NULL)
	{
		ft_perror(NULL, "philo", "system error (malloc failed)");
		return (-1);
	}
	return (0);
}

int	make_forks(t_ph_parms *parms, pthread_mutex_t **forks)
{
	int	i;

	*forks = malloc(parms->num_philos * sizeof(pthread_mutex_t));
	i = 0;
	while (i < parms->num_philos)
	{
		if (pthread_mutex_init(*forks + i, NULL) != -1)	
		{
			ft_perror(NULL, "philo" "could not create mutex");
			return (-1);
		}
		i++;
	}
}

int	make_philo_structs(t_ph_parms *parms, t_ph_philo **philo)
{
	*philo_structs = malloc(parms->num_philos * sizeof(t_ph_philo));
	if (*philo_structs == NULL)
		return (-1);
	return (0);
}

int	destroy_forks(t_ph_parms *parms, pthread_mutex_t ***forks)
{
	int	i;

	i = 0;
	while (i < parms->num_philos)
	{
		if (pthread_mutex_destroy(forks + i, NULL) != 0)
		{
			ft_perror(NULL, NULL, "system error: could not destroy mutex");
			return (-1);
		}
		i++;
	}
	free(*forks);
}


