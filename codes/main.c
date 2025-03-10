#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *line;        // 用于存储用户输入的命令行
    t_shell shell;     // shell的主要数据结构

    // 初始化shell环境
    init_shell(&shell, envp);
    set_custom_prompt(&shell, "\033[1;32mminishell\033[0m$ ");
    
    while (1)
    {
        // 设置信号处理
        signal_handler();
        // 显示提示符并获取用户输入
        line = readline(shell.prompt);
        if (!line)     // 处理EOF（Ctrl+D）
            break;
        if (*line)     // 如果输入不为空
        {
            add_history(line);    // 添加到命令历史
            parse_and_execute(&shell, line);  // 解析并执行命令
        }
        free(line);    // 释放读取的命令行
    }
    cleanup_shell(&shell);    // 清理shell环境
    return (0);
}

void set_custom_prompt(t_shell *shell, const char *prompt)
{
    if (shell->prompt)
        free(shell->prompt);
    shell->prompt = strdup(prompt);
}
