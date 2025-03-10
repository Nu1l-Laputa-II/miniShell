#include "minishell.h"

// 检查命令是否是内建命令
int is_builtin(char *cmd)
{
    return (!strcmp(cmd, "cd") || !strcmp(cmd, "exit") ||
            !strcmp(cmd, "env") || !strcmp(cmd, "echo") ||
            !strcmp(cmd, "pwd") || !strcmp(cmd, "export") ||
            !strcmp(cmd, "unset") || !strcmp(cmd, "history"));
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
    else if (!strcmp(args[0], "pwd"))
        return execute_pwd();
    else if (!strcmp(args[0], "export"))
        return execute_export(shell, args);
    else if (!strcmp(args[0], "unset"))
        return execute_unset(shell, args);
    else if (!strcmp(args[0], "history"))
    {
        display_history();
        return 0;
    }
    return 1;
}

int execute_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return 0;
    }
    return 1;
}

int execute_export(t_shell *shell, char **args)
{
    if (!args[1])
        return 1;
    char *equals = strchr(args[1], '=');
    if (!equals)
        return 1;

    *equals = '\0';
    char *value = equals + 1;
    
    t_env *env = shell->env;
    while (env)
    {
        if (!strcmp(env->key, args[1]))
        {
            free(env->value);
            env->value = strdup(value);
            return 0;
        }
        env = env->next;
    }
    return 1;
}
