# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwozniak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/10 16:54:57 by jwozniak          #+#    #+#              #
#    Updated: 2024/08/10 16:54:59 by jwozniak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
SRCS	:=	main.c init.c philo.c forks.c utils.c
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus