/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:13:29 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/02 12:19:27 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark P (parse) */

/* if argc is not correct, print usage message and return -1
 * parse num_philos, time_die, time_eat, time_sleep and - if given -
 * times_must_eat into main struct
 * If arguments are not in correct format (int or long, not bigger than long int
 * max) print an error message and return -1
 * If parsing was succesful, return 0.
 */
int	parse(t_main *main, int argc, char **argv)
{
	if (argc < 4 || argc > 5)
		return (return_error(USAGE, -1));
	main->num_philos = (int) ft_atol(argv[1]);
	if (main->num_philos < 2)
		return (return_error(PHILOS, -1));
	main->time_die = ft_atol(argv[1]);
	main->time_eat = ft_atol(argv[2]);
	main->time_sleep = ft_atol(argv[3]);
	if (main->time_die == -1 || main->time_eat == -1 
			|| main->time_sleep == -1)
		return (return_error(TIME, -1));
	if (argc == 5)
	{
		main->times_must_eat = ft_atol(argv[4]);
		if (main->times_must_eat == -1)
			return (return_error(TIME, -1));
	}
	else
		main->times_must_eat = -1;
	return (0);
}

