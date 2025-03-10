# MiniShell API 文档

## 核心函数接口

### Shell 初始化和清理

```c
void init_shell(t_shell *shell, char **envp);
```
初始化 shell 环境。
- 参数：
  - shell: shell 结构体指针
  - envp: 环境变量数组
- 返回值：无

```c
void cleanup_shell(t_shell *shell);
```
清理 shell 资源。
- 参数：
  - shell: shell 结构体指针
- 返回值：无

### 命令解析和执行

```c
void parse_and_execute(t_shell *shell, char *line);
```
解析并执行命令行。
- 参数：
  - shell: shell 结构体指针
  - line: 命令行字符串
- 返回值：无

```c
int execute_command(t_shell *shell, char **args);
```
执行外部命令。
- 参数：
  - shell: shell 结构体指针
  - args: 命令参数数组
- 返回值：命令执行状态

### 内建命令

```c
int is_builtin(char *cmd);
```
检查是否为内建命令。
- 参数：
  - cmd: 命令名
- 返回值：1 如果是内建命令，否则为 0

```c
int execute_builtin(t_shell *shell, char **args);
```
执行内建命令。
- 参数：
  - shell: shell 结构体指针
  - args: 命令参数数组
- 返回值：命令执行状态

### 环境变量管理

```c
void init_env(t_shell *shell, char **envp);
```
初始化环境变量。
- 参数：
  - shell: shell 结构体指针
  - envp: 环境变量数组
- 返回值：无

```c
char *get_env_value(t_env *env, char *key);
```
获取环境变量值。
- 参数：
  - env: 环境变量链表
  - key: 变量名
- 返回值：变量值，未找到返回 NULL

### 信号处理

```c
void signal_handler(void);
```
设置信号处理函数。
- 参数：无
- 返回值：无

### 管道处理

```c
int handle_pipes(t_shell *shell, char **args);
```
处理命令管道。
- 参数：
  - shell: shell 结构体指针
  - args: 命令参数数组
- 返回值：执行状态

### 提示符管理

```c
void set_custom_prompt(t_shell *shell, const char *prompt);
```
设置自定义提示符。
- 参数：
  - shell: shell 结构体指针
  - prompt: 新的提示符字符串
- 返回值：无

### 新增内建命令

```c
int execute_pwd(void);
```
显示当前工作目录。
- 返回值：执行状态

```c
int execute_export(t_shell *shell, char **args);
```
设置环境变量。
- 参数：
  - shell: shell 结构体指针
  - args: 命令参数数组
- 返回值：执行状态

```c
int execute_unset(t_shell *shell, char **args);
```
删除环境变量。
- 参数：
  - shell: shell 结构体指针
  - args: 命令参数数组
- 返回值：执行状态

## 数据结构

### 环境变量节点
```c
typedef struct s_env {
    char *key;             // 变量名
    char *value;          // 变量值
    struct s_env *next;   // 下一个节点
} t_env;
```

### Shell 结构体
```c
typedef struct s_shell {
    t_env *env;           // 环境变量链表
    int status;           // 命令执行状态
} t_shell;
```
