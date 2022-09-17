/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:56:52 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/16 15:07:31 by hoomen           ###   ########.fr       */
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
# define USAGE "Usage: \033[44m./philo \033[42m<nbr_of_philosophers> \033[43m<time\
_to_die> \033[45m<time_to_eat> \033[46m<time_to_sleep> \033[43m[max meals]\033[40m"
# define INV_TIME "Please provide time in whole milliseconds (max 2.000.000)."
# define INV_PH "Please provide a valid number of philosophers (max 200)."
# define INV_ME "Number of meals invalid. Please provide a valid number (max 2.000.000); \
alternatively, leave this parameter out."
# define NO_PH "Number of philosophers is 0. No simulation is possible."

# define FORK "\033[36;1mhas taken a fork\033[0m \U0001F374"
# define EAT "\033[33;1mis eating\033[0m \U0001F35D"
# define SLEEP "\033[35;1mis sleeping\033[0m \U0001F4A4"
# define THINK "\033[32;1mis thinking\033[0m \U0001F4AD"
# define DIE "\033[31;1mdied\033[0m \U0001FAA6"

#endif

