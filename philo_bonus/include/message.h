/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:56:52 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/17 13:59:06 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

/* mark E */

# define ERR "Error:"
# define MALLOC_ERR "System error: Failed to allocate memory."
# define THREAD_ERR "System error: Failed to create thread."
# define SEM_ERR "System error: Failed to open semaphores."
# define FORK_ERR "System error: Failed to create child process."
# define UNDEF_CHILD_PROC "Abort: Undefined error in child process"
# define ARGS "Invalid arguments."
# define USAGE "Usage: ./philo <nbr_of_philosophers> <time\
_to_die> <time_to_eat> <time_to_sleep> [max meals]."
# define INV_TIME "Please provide time in whole milliseconds."
# define INV_PH "Please provide a valid number of philosophers (max 200)."
# define INV_ME "Please provide a valid number of meals; alternatively, \
leave this parameter out."
# define NO_PH "Number of philosophers is 0. No simulation is possible."
# define START_SATED ""

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

#endif

