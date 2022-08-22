/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:42:33 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/22 19:32:17 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ph_parms		parms;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	t_ph_philo		*philo_structs;
	int				i;

	if (ph_parse (argc, argv, &parms) == -1)
		return (1);
	if (make_philos(&philos, parms) == -1 || make_forks(&forks, parms) == -1
			|| make_structs(&philo_structs, parms) == -1)
		return (2);
	while (i < parms->num_philos)
	{
		philo_structs[i]->parms = parms;
		philo_structs[i]->right = forks[i];
		if (i == 0)
			philo_struct[i]->left = forks[parms->num_philos - 1];
		else
			philo_struct[i]->left = forks[i - 1];
		if (pthread_create(philos + i, NULL, philo_structs + i))
			return (1);
		i++;
	}
	return (0);
}

