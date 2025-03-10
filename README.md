# MiniShell

一个简单的 Shell 实现，支持基本的命令执行、内建命令和环境变量管理。

## 功能特性

- 命令行解析和执行
- 内建命令支持 (cd, exit, env, echo)
- 环境变量管理
- 信号处理 (Ctrl+C, Ctrl+\)
- 命令历史记录

## 快速开始

### 编译要求

- GCC 编译器
- readline 库
- Make 工具

### 安装步骤

```bash
# 克隆仓库
git clone <repository-url>
cd miniShell

# 编译项目
make

# 运行 shell
./minishell
```

### 基本使用

```bash
minishell$ ls -l
minishell$ cd directory
minishell$ env
minishell$ echo hello
minishell$ exit
```

## 项目文档

- [设计文档](doc/design.md) - 详细的架构设计和实现说明
- [API文档](doc/api.md) - 函数接口文档

## 许可证

[MIT License](LICENSE)
