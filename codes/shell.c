#include "minishell.h"

// 初始化shell结构
void init_shell(t_shell *shell, char **envp)
{
    shell->status = 0;           // 初始化状态为0
    init_env(shell, envp);       // 初始化环境变量
}

// 清理shell结构
void cleanup_shell(t_shell *shell)
{
    t_env *current;
    t_env *next;

    // 释放环境变量链表
    current = shell->env;
    while (current)
    {
        next = current->next;
        free(current->key);      // 释放键
        free(current->value);    // 释放值
        free(current);           // 释放节点
        current = next;
    }
}
