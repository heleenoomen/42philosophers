# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 15:35:03 by hoomen            #+#    #+#              #
#    Updated: 2022/09/17 15:33:10 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH		= src
INCFLAGS	= -I include

CC			= cc
FLAGS		= -Wall -Werror -Wextra -fsanitize=thread

NAME		= philo
HEADER		= include/philo.h
SRC			= action.c check.c exit_program.c init_structs.c main.c mutex.c\
			  set.c simulation.c time.c utils.c watcher.c
OBJ			= $(addprefix obj/,$(notdir $(SRC:.c=.o)))

$(NAME) : $(OBJ) 
	$(CC) $(FLAGS) -o $@ $^ -pthread

obj/%.o : %.c $(HEADER) | obj
	$(CC) $(FLAGS) $(INCFLAGS) -c $< -o $@

obj :
	mkdir obj

all : $(NAME)

bonus : $(NAME)

clean :
	rm -rf obj

fclean : clean
	rm -f $(NAME)

re : clean all

.PHONY : all clean fclean re bonus