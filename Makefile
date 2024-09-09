# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 18:12:57 by ykai-yua          #+#    #+#              #
#    Updated: 2024/09/09 23:31:01 by ykai-yua         ###   ########.fr        #
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
       $(SRCS_DIR)/check.c \
	   $(SRCS_DIR)/utils.c

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