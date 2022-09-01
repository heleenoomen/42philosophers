/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:13:29 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/01 15:17:44 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark P (parse) */

int	parse(t_parms *parms, int argc, char **argv)
{
	if (argc < 4 || argc > 5)
		return (putstr_return(USAGE, -1));
	parms->num_philos = (int) ft_atol(argv[1]);
	if (parms->num_philos < 2)
		return (putstr_return(PHILOS, -1));
	parms->time_die = ft_atol(argv[1]);
	parms->time_eat = ft_atol(argv[2]);
	parms->time_sleep = ft_atol(argv[3]);
	if (parms->time_die == -1 || parms->time_eat == -1 
			|| parms->time_sleep == -1)
		return (putstr_return(TIME, -1));
	if (argc == 5)
	{
		parms->times_must_eat = ft_atol(argv[4]);
		if (parms->times_must_eat == -1)
			return (putstr_return(TIME, -1));
	}
	return (0);
}

