# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkarlon- <lkarlon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 18:07:03 by chermist          #+#    #+#              #
#    Updated: 2019/10/10 22:20:27 by chermist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = gcc

INCDIR = -I libft/includes -I inc

LIBDIR = -L libft

LIBNAME = libft/libft.a

LIB = -lft

CFLAGS = -g $(INCDIR)

SRCDIR = src

SRC = 	main.c \
		support.c \
		parse.c \
	  	algo.c \
		lem_in.c \

OBJ = $(SRC:.c=.o)

vpath %.c $(SRCDIR)

all: DEPS $(NAME)

$(NAME): $(OBJ) $(LIBNAME)
	$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) $(LIB) $(OBJ) -o $@

DEPS:
	make -C libft/

$(LIBNAME):
	make -C libft/

%.o: %.c %.h

clean:
	make -C libft $@
	rm -f $(OBJ)

fclean: clean
	make -C libft $@
	rm -f $(NAME)

re: fclean all
