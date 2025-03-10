#ifndef MINISHELL_H
# define MINISHELL_H

// 系统所需头文件
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

// 环境变量链表结构
typedef struct s_env
{
    char *key;             // 环境变量名
    char *value;           // 环境变量值
    struct s_env *next;    // 指向下一个环境变量
} t_env;

// shell主要数据结构
typedef struct s_shell
{
    t_env *env;           // 环境变量链表
    int status;           // 最后执行的命令的退出状态
} t_shell;

// Shell初始化和清理函数声明
void init_shell(t_shell *shell, char **envp);
void cleanup_shell(t_shell *shell);

// 命令解析和执行函数声明
void parse_and_execute(t_shell *shell, char *line);
int execute_command(t_shell *shell, char **args);

// 内建命令函数声明
int is_builtin(char *cmd);
int execute_builtin(t_shell *shell, char **args);

// 环境变量处理函数声明
void init_env(t_shell *shell, char **envp);
char *get_env_value(t_env *env, char *key);

// 信号处理函数声明
void signal_handler(void);

#endif
