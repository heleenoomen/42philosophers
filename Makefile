# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 15:35:03 by hoomen            #+#    #+#              #
#    Updated: 2022/09/05 13:46:05 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH		= src
INCFLAGS	= -I include

CC			= cc
FLAGS		= -Wall -Werror -Wextra -g

NAME		= philo
HEADER		= include/philo.h
SRC			= main.c utils.c init_controller.c fork.c philo.c threads.c\
			  actions.c time.c exit_program.c
OBJ			= $(addprefix obj/,$(notdir $(SRC:.c=.o)))

$(NAME) : $(OBJ) 
	$(CC) $(FLAG) -o $@ $^ -pthread

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
