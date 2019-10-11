# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 18:07:03 by chermist          #+#    #+#              #
#    Updated: 2019/10/11 18:31:55 by chermist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = gcc

INCDIR = -I libft/includes -I ./inc

LIBDIR = -L ./libft

OBJDIR = ./obj

LIBNAME = libft/libft.a

LIB = -lft

CFLAGS = $(INCDIR)

SRCDIR = ./src

SRC = 	main.c \
		support.c \
		parse.c \
	  	algo.c \
		lem_in.c \

OBJ = $(SRC:.c=.o)

vpath %.c $(SRCDIR)

all: DEPS $(NAME)

#$(OBJ_DIR):
#	@mkdir -p $(OBJ_DIR)

$(NAME):  $(OBJ) $(LIBNAME)
	@echo "\033[35mCompiling ./lem-in\033[0m"
	@$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) $(LIB) $(OBJ) -o $@
	@echo "\033[1;32m./lem-in was built\033[0m"

DEPS:
	@make -C libft/

$(LIBNAME):
	@make -C libft/

%.o: %.c %.h

clean:
	@make -C libft $@
	@rm -f $(OBJ)
	@echo "\033[3;36mProject cleaned\033[0m"

fclean: clean
	@make -C libft $@
	@ rm -f $(NAME)
	@echo "\033[3;36mProject fully cleaned\033[0m"

re: fclean all

norm:
	@norminette src/*

.PHONY: all clean fclean re norm
