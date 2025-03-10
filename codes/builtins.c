#include "minishell.h"

// 检查命令是否是内建命令
int is_builtin(char *cmd)
{
    return (!strcmp(cmd, "cd") || !strcmp(cmd, "exit") ||
            !strcmp(cmd, "env") || !strcmp(cmd, "echo"));
}

// 执行内建命令
int execute_builtin(t_shell *shell, char **args)
{
    // cd命令实现
    if (!strcmp(args[0], "cd"))
    {
        if (args[1] == NULL)         // 无参数时切换到HOME目录
            return chdir(getenv("HOME"));
        return chdir(args[1]);       // 切换到指定目录
    }
    // exit命令实现
    else if (!strcmp(args[0], "exit"))
    {
        cleanup_shell(shell);
        exit(shell->status);
    }
    // env命令实现：显示所有环境变量
    else if (!strcmp(args[0], "env"))
    {
        t_env *current = shell->env;
        while (current)
        {
            printf("%s=%s\n", current->key, current->value);
            current = current->next;
        }
        return 0;
    }
    return 1;
}
