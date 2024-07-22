# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 19:30:49 by jpancorb          #+#    #+#              #
#    Updated: 2024/07/22 19:36:25 by jpancorb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRCS	= dinner.c error.c init.c main.c monitor_print.c syncro.c utils.c
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