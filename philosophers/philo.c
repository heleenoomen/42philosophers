/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:52:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/02 13:55:17 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark H	philo.h
 * mark P	parse.c
 * mark I	initialize.c
 * mark U	utils.c
 * mark M	philo.c
 * mark F	free.c
 * mark T	time.c
 * mark R	threads.c
 */

/* parse, initialize structs and create threads
 * then, vigilize if one of the philosophers died
 * if a philosopher dies, break out of whileloop, free program and return
 */ /* mark m */
int	main(int argc, char **argv)
{
	t_main		main;
	t_philo		*philos;
	int			i;

	if (parse(&main, argc, argv) == -1)
		retur (1);
	if (init(&main, &philos) == -1)
		return (2);
	if (create_threads(main, philos) == -1)
		return (3);
	while (1)
	{
		i = 0;
		while (i < main.num_philos)
		{
			if ((philos + i)->died != FALSE)
				break ;
			i++;
		}
	}
	free_philo(philosophers, philos, parms);
	return (0);
}

