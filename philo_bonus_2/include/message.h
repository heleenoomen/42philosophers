/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:56:52 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/08 13:14:15 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

/* mark E */

# define ERR "Error:"
# define MALLOC_ERR "Failed at allocating memory."
# define THREAD_ERR "Failed at creating thread."
# define MUTEX_ERR "Failed at initializing mutex."
# define ARGS "Invalid arguments."
# define USAGE "Usage: ./philo <nbr_of_philosophers> <time\
_to_die> <time_to_eat> <time_to_sleep> [max meals]."
# define INV_TIME "Please provide time in whole milliseconds (max UINT_MAX)."
# define INV_PH "Please provide a valid number of philosophers (max 200)."
# define INV_ME "Number of meals invalid. Please provide a valid number (max INT_MAX); \
alternatively, leave this parameter out."
# define NO_PH "Number of philosophers is 0. No simulation is possible"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

#endif

