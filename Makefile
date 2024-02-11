# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: m3ayz00 <m3ayz00@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 18:34:38 by msaadidi          #+#    #+#              #
#    Updated: 2024/02/10 20:43:02 by m3ayz00          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc -Wall -Wextra -Werror 
SRCS = pipex.c pipex_utils.c check_parse.c ft_split.c ft_strtrim.c mem_management.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)


$(NAME) : $(OBJS)

clean : 
	rm -rf $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.SECONDARY : $(OBJS)

.PHONY : all clean fclean re 