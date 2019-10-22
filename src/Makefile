# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chermist <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 01:10:20 by chermist          #+#    #+#              #
#    Updated: 2019/10/23 01:27:02 by chermist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

INC_DIR = ./inc
SRC_DIR = ./src
OBJ_DIR = ./obj

LIB_DIR = ./libft
LIBFT = $(LIB_DIR)/libft.a

SRC =	main.c \
		support.c \
		parse.c \
	  	algo.c \
		lem_in.c \
		moves.c

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

CC = gcc

#CFLAGS = -g -c -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIB_DIR) `sdl2-config --cflags`
CFLAGS = -c -I$(INC_DIR) -I$(LIB_DIR) `sdl2-config --cflags`

LFLAGS = -L$(LIB_DIR) -lft `sdl2-config --libs` -lSDL2_gfx -lSDL2_ttf -lm

vpath %.c $(SRC_DIR)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@printf "%-54c\rLinking...\n" ' '
	@$(CC) -o $@ $^ $(LFLAGS)
	@printf "Done !\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "Compiling... %-21s => %-21s\r" $^ $@

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	@make -C $(LIB_DIR) clean
	@rm -f $(OBJ)
	@printf "Removed objs\n"

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)
	@printf "Removed $(NAME)\n"

re: fclean all

.PHONY: all clean fclean re