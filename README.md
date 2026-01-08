# minishell

## Project Overview
`minishell` is a minimal Unix shell inspired by Bash.

It supports command execution, pipes, redirections, environment variables, variable expansions, heredoc and signal handling.

## Core Concepts
- Process creation (`fork`, `execve`)
- File descriptor manipulation
- Signal handling (`SIGINT`, `SIGQUIT`)
- Command parsing & tokenization
- Environment variable management
- Command execution
- Heredoc
- Built-in commands such as `unset`, `export`, etc.

## Build
```
make
```

## Usage

```
./minishell
```

## Supported Features

### Built-ins
- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Redirections

```
>   >>   <   <<
```

### Pipes
```
ls | grep src | wc -l
```

### Environment variables
```
echo $PATH
export VAR=value
```

### Signals
- `Ctrl+C` : interrupts current command
- `Ctrl+D` : exits shell
- `Ctrl+\` : ignored
