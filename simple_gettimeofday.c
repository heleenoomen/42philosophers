/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_gettimeofday.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 19:04:56 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/22 19:22:24 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(void)
{
	struct timeval	tv1;
	struct timeval	tv2;

	gettimeofday(&tv1, NULL);
	usleep(3000);
	gettimeofday(&tv2, NULL);
	printf("time in microseconds = %d\n", (tv2.tv_usec - tv1.tv_usec) / 1000);
	return (0);
}

	
