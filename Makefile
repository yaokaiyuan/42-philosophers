# 项目名称
NAME = philo

# 编译器
CC = cc

# 编译选项
CFLAGS = -Wall -Wextra -Werror -pthread

# 包含头文件的目录
INCLUDES = -I includes

# 源文件目录
SRCS_DIR = srcs

# 源文件
SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/philo.c \
       $(SRCS_DIR)/init.c

# 目标文件
OBJS = $(SRCS:.c=.o)

# 头文件
HEADERS = includes/philo.h

# 默认目标
all: $(NAME)

# 编译规则
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# 生成目标文件的规则
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 清理目标文件
clean:
	rm -f $(OBJS)

# 清理所有生成的文件
fclean: clean
	rm -f $(NAME)

# 重新编译
re: fclean all

# 声明伪目标
.PHONY: all clean fclean re