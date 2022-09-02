/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:09:43 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/02 13:06:58 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mark T (time) */

/* sets the time in 'time' to the current time */
int	set_time(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		return (-1);
	return (0);
}

/* returns the time passed in milliseconds since the time saved in 'beginning' 
 */
long	get_timediff(struct timeval *beginning)
{
	struct timeval current;

	if (gettimeofday(&current, NULL))
		return (-1);
	return ((current->tv_usec - beginning->tv_usec) / 1000);
}

