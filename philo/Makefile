# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 18:12:57 by ykai-yua          #+#    #+#              #
#    Updated: 2024/12/17 16:28:46 by ykai-yua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

INCLUDES = -I includes

SRCS_DIR = srcs

SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/philo.c \
       $(SRCS_DIR)/init.c \
       $(SRCS_DIR)/free.c \
	   $(SRCS_DIR)/monitor.c \
	   $(SRCS_DIR)/parcing.c \
	   $(SRCS_DIR)/print.c \
	   $(SRCS_DIR)/time.c

OBJS = $(SRCS:.c=.o)

HEADERS = includes/philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re