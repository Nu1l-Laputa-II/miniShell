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
        if (!strcmp(token, "|"))
            shell->pipe_count++;
        args[i] = token;
        i++;
        token = strtok(NULL, " \t\r\n\a");
    }
    args[i] = NULL;      // 参数数组以NULL结尾

    // 如果有命令则执行
    if (args[0] != NULL)
    {
        if (shell->pipe_count > 0)
            shell->status = handle_pipes(shell, args);
        else if (is_builtin(args[0]))     // 检查是否是内建命令
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

int handle_pipes(t_shell *shell, char **args)
{
    int i, j, k;
    int pipe_fd[2];
    pid_t pid;
    int in_fd = 0;
    
    for (i = 0; i <= shell->pipe_count; i++)
    {
        pipe(pipe_fd);
        
        if ((pid = fork()) == 0)
        {
            if (in_fd != 0)
            {
                dup2(in_fd, 0);
                close(in_fd);
            }
            if (i < shell->pipe_count)
                dup2(pipe_fd[1], 1);
            
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            
            // 执行命令
            char *cmd[64];
            k = 0;
            for (j = 0; args[j] != NULL && strcmp(args[j], "|") != 0; j++)
                cmd[k++] = args[j];
            cmd[k] = NULL;
            
            execvp(cmd[0], cmd);
            exit(1);
        }
        
        close(pipe_fd[1]);
        if (in_fd != 0)
            close(in_fd);
        in_fd = pipe_fd[0];
        
        // 移动到下一个命令
        while (*args && strcmp(*args, "|") != 0)
            args++;
        if (*args)
            args++;
    }
    
    // 等待所有子进程
    while (wait(NULL) > 0);
    return 0;
}
