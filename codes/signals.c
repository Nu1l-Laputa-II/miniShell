#include "minishell.h"

// 处理SIGINT信号（Ctrl+C）
static void handle_sigint(int sig)
{
    (void)sig;                   // 忽略未使用的参数警告
    write(1, "\n", 1);          // 输出换行
    rl_on_new_line();           // readline新行处理
    rl_replace_line("", 0);     // 清空当前行
    rl_redisplay();             // 重新显示提示符
}

// 设置信号处理函数
void signal_handler(void)
{
    signal(SIGINT, handle_sigint);   // 设置Ctrl+C处理函数
    signal(SIGQUIT, SIG_IGN);        // 忽略Ctrl+\
}
