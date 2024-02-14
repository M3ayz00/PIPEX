# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 18:34:38 by msaadidi          #+#    #+#              #
#    Updated: 2024/02/14 14:08:45 by msaadidi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc 
CFLAGS = -Wall -Wextra -Werror 
MSRCS = mandatory/pipex.c mandatory/pipex_utils.c mandatory/check_parse.c 
SMSRCS = string_manip/ft_split.c string_manip/mem_management.c

MOBJS = $(MSRCS:.c=.o)

SMOBJS = $(SMSRCS:.c=.o)

all : $(NAME)

$(NAME) : $(SMOBJS) $(MOBJS) 
	@$(CC) $(CFLAGS) $(MOBJS) $(SMOBJS) -o $(NAME)

clean :
	@rm -rf $(MOBJS) $(SMOBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.SECONDARY : $(MOBJS) $(SMOBJS)

.PHONY : all clean fclean re 