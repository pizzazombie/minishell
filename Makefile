  
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dholiday <dholiday@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/02 17:03:41 by tguillem          #+#    #+#              #
#    Updated: 2019/09/05 20:55:41 by dholiday         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTPATH = ./Libft
LIBFT = $(LIBFTPATH)/libft.a

CFLAGS =  -I. -I$(LIBFTPATH) -Iinc -g3
CC = gcc


SRC = main.c commands.c quotes.c helpers.c cd.c env.c setenv.c unsetenv.c useful_helpers.c run_commands.c 

OBJ = $(SRC:%.c=%.o)

NAME = minishell

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ) 
	gcc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ) : ./shell.h

$(LIBFT) :
	make -C $(LIBFTPATH)

clean:
	make clean -C $(LIBFTPATH)
	rm -f $(OBJ) 

fclean: clean
	make fclean -C $(LIBFTPATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re