# 项目名称
NAME = minishell
# 编译器设置
CC = gcc
# 编译选项：开启所有警告
CFLAGS = -Wall -Wextra -Werror
# 链接选项：链接readline库
LDFLAGS = -lreadline

# 源文件列表
SRCS = main.c execute.c builtins.c env.c shell.c signals.c
# 目标文件列表
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(NAME)

# 链接目标文件生成可执行文件
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

# 编译规则：.c文件编译为.o文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理目标文件
clean:
	rm -f $(OBJS)

# 完全清理（包括可执行文件）
fclean: clean
	rm -f $(NAME)

# 重新编译
re: fclean all

# 伪目标声明
.PHONY: all clean fclean re
