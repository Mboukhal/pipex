# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboukhal <mboukhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 21:39:40 by mboukhal          #+#    #+#              #
#    Updated: 2022/03/10 15:03:01 by mboukhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL		= all
NAME				= pipex

CFILES				= pipex.c ft_strlen.c ft_strncmp.c ft_strchr.c ft_split.c 		\
					ft_bzero.c ft_memset.c ft_strlcat.c ft_strlcpy.c pipex_utils.c 	\
					ft_isalpha.c exit_error.c

CFLAGS				= -Wall -Wextra -Werror
RM					= rm -rf
CC					= cc

OBJ			= $(CFILES:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -c $< 

$(NAME):$(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ)  $(INCLUDES)

fclean: clean
	@$(RM) $(NAME)

clean:
	@$(RM) $(OBJ)

re: fclean all

all: $(NAME)

.PHONY: re fclean all clean