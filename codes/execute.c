#include "minishell.h"

// 解析并执行命令行
void parse_and_execute(t_shell *shell, char *line)
{
    char **args;          // 存储解析后的命令参数数组
    char *token;          // 用于存储分割后的字符串
    int i = 0;

    // 为参数数组分配内存（最多64个参数）
    args = malloc(sizeof(char *) * 64);
    // 使用空格、制表符等作为分隔符拆分命令行
    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " \t\r\n\a");
    }
    args[i] = NULL;      // 参数数组以NULL结尾

    // 如果有命令则执行
    if (args[0] != NULL)
    {
        if (is_builtin(args[0]))     // 检查是否是内建命令
            shell->status = execute_builtin(shell, args);
        else                         // 执行外部命令
            shell->status = execute_command(shell, args);
    }
    free(args);
}

// 执行外部命令
int execute_command(t_shell *shell, char **args)
{
    pid_t pid;
    int status;

    pid = fork();        // 创建子进程
    if (pid == 0)        // 子进程
    {
        if (execvp(args[0], args) == -1)  // 执行命令
        {
            printf("minishell: command not found: %s\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)    // fork失败
    {
        printf("Error forking process\n");
        return 1;
    }
    else                 // 父进程
    {
        waitpid(pid, &status, WUNTRACED);  // 等待子进程结束
    }
    return WEXITSTATUS(status);     // 返回命令执行状态
}
