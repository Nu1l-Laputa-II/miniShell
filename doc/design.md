# MiniShell 设计文档

## 整体架构

MiniShell 采用模块化设计，主要包含以下几个核心组件：

### 1. 命令处理流程

```plaintext
用户输入 -> 命令解析 -> 命令执行 -> 显示结果
```

### 2. 核心模块

#### 2.1 主程序 (main.c)
- 初始化 shell 环境
- 实现命令行读取循环
- 信号处理设置

#### 2.2 命令执行 (execute.c)
- 命令解析（parse_and_execute）
- 外部命令执行（execute_command）
- 进程创建和管理

#### 2.3 内建命令 (builtins.c)
- cd：目录切换
- exit：退出 shell
- env：显示环境变量
- echo：输出信息
- pwd：显示当前工作目录
- export：设置环境变量
- unset：删除环境变量

#### 2.4 环境变量管理 (env.c)
- 环境变量初始化
- 变量查询和修改
- 链表数据结构管理

#### 2.5 信号处理 (signals.c)
- Ctrl+C (SIGINT) 处理
- Ctrl+\ (SIGQUIT) 处理

#### 2.6 管道处理 (execute.c)
- 支持多重管道
- 进程间通信
- 文件描述符管理

#### 2.7 提示符定制 (main.c)
- 自定义提示符
- 颜色支持
- 动态更新

### 3. 数据结构

```c
typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_shell {
    t_env *env;
    int status;
    char *prompt;         // 自定义提示符
    int pipe_count;       // 管道数量
} t_shell;
```

### 4. 代码阅读顺序

1. minishell.h - 了解整体结构和接口定义
2. main.c - 理解主程序流程
3. execute.c - 学习命令执行机制
4. builtins.c - 了解内建命令实现
5. env.c - 研究环境变量管理
6. signals.c - 学习信号处理方式

### 5. 扩展性设计

项目预留了以下扩展点：
- 新增内建命令
- 添加管道支持
- 实现重定向
- 增加作业控制
