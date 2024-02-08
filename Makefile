# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 18:34:38 by msaadidi          #+#    #+#              #
#    Updated: 2024/02/08 00:11:02 by m3ayz00          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc -Wall -Wextra -Werror
SRCS = pipex.c check_parse.c ft_split.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)

clean : 
	@rm -rf $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all
