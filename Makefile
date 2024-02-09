# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 18:34:38 by msaadidi          #+#    #+#              #
#    Updated: 2024/02/09 16:59:03 by msaadidi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc -Wall -Wextra -Werror 
SRCS = pipex.c check_parse.c ft_split.c ft_strtrim.c mem_management.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)

clean : 
	@rm -rf $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all
