# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 15:35:03 by hoomen            #+#    #+#              #
#    Updated: 2022/09/09 16:59:33 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH		= src
INCFLAGS	= -I include

CC			= cc
FLAGS		= -Wall -Werror -Wextra -fsanitize=thread

NAME		= philo
HEADER		= include/philo.h
SRC			= main.c utils.c init_controller.c fork.c philo.c threads.c\
			  actions.c time.c exit_program.c watcher.c
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
