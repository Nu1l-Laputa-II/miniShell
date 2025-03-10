#include "minishell.h"

// 初始化环境变量
void init_env(t_shell *shell, char **envp)
{
    int i;
    char *key;
    char *value;
    t_env *new;
    t_env *current;

    shell->env = NULL;
    // 遍历环境变量数组
    for (i = 0; envp[i]; i++)
    {
        key = strdup(envp[i]);           // 复制环境变量字符串
        value = strchr(key, '=');        // 查找等号位置
        if (value)
        {
            *value = '\0';               // 将等号替换为字符串结束符
            value++;                     // value指向值的起始位置
            // 创建新的环境变量节点
            new = malloc(sizeof(t_env));
            new->key = strdup(key);      // 复制键
            new->value = strdup(value);  // 复制值
            new->next = NULL;
            
            // 将新节点添加到链表末尾
            if (!shell->env)
                shell->env = new;
            else
            {
                current = shell->env;
                while (current->next)
                    current = current->next;
                current->next = new;
            }
        }
        free(key);
    }
}

// 获取环境变量值
char *get_env_value(t_env *env, char *key)
{
    while (env)
    {
        if (!strcmp(env->key, key))      // 找到匹配的环境变量
            return env->value;
        env = env->next;
    }
    return NULL;    // 未找到返回NULL
}
