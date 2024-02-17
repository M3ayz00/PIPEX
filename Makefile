# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 18:34:38 by msaadidi          #+#    #+#              #
#    Updated: 2024/02/17 15:49:27 by msaadidi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc 
CFLAGS = -Wall -Wextra -Werror 
SRCS = pipex.c pipex_utils.c pipex_utils2.c ft_split.c mem_management.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.SECONDARY : $(OBJS) 

.PHONY : all clean fclean re 