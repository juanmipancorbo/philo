# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 19:30:49 by jpancorb          #+#    #+#              #
#    Updated: 2024/07/28 14:31:07 by jpancorb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRCS	= dinner.c handlers.c parser.c main.c monitor.c syncro.c utils.c
HEADER	= philo.h
CFLAGS	= -Wall -Werror -Wextra 

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		cc $(CFLAGS) -o $@ $^

%.o: %.c $(HEADER)
		cc $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re