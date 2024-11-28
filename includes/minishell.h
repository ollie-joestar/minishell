/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/28 23:52:50 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>

// exec types
# define BUILTIN 69
# define CMD 420

// pipes
# define RD 0
# define WR 1
// quotes
# define SQ '\''
# define DQ '\"'
# define SLASH '\\'
# define DOLLAR '$'

typedef enum e_token_type {
    WORD = 0,
    PIPE = 1,
    INPUT = 2,
    HEREDOC = 3,
    REPLACE = 4,
    APPEND = 5
}   t_token_type;

typedef struct s_token {
    char		*word;
    bool		quote;
    bool		single_or_double; // false = single, true = double
    t_token_type	type;
    struct s_token	*next;
    struct s_token	*prev;
}			t_token;

typedef	struct	s_expansion {
    size_t	index;
    size_t	start;
    size_t	end;
    char	*result;
    char	*temp;
    char	*var_name;
    char	*var_value;
}		t_expansion;

typedef struct s_input {
	int		type; // HERE_DOC | FILE
	char		*file;
	struct s_input	*next;
	struct s_input	*prev;
}			t_input;

typedef struct s_output {
	int		type; // REPLACE | APPEND
	char		*file;
}			t_output;

typedef struct s_envlist {
	char			*name;
	char			*value;
	struct s_envlist	*next;
	struct s_envlist	*prev;
}				t_envlist;

typedef struct s_exec {
	int		type; // BUILTIN | CMD
	t_input		*in; // linked list of input files
	t_output	*out; // linked list of output files
	int		piped; // 1 if the command is piped
	int		pipe[2]; // pipe file descriptors
	char		*cmd; // full path to the command
	char		**av;
	struct s_exec	*prev;
	struct s_exec	*next;
}			t_exec;


typedef struct s_data
{
	pid_t			pid; // to store last child process id
	t_exec			*exec; // to store the current command data
	char			**ev; // to store the environment variables
	t_envlist		*env; // to store the environment variables in linked list
	char			**path; // to store the path variable after splitting
	int			status; // to store the exit status of the last command
	struct sigaction	sa; // to store the signal action
	char			*line; //lineread
	t_token			*token; // to store the list of tokenized commands
	t_expansion		*expansion; // to store the expansion data
	int			exit_status; // to store the exit status of last command
}				t_data;

/* Signal functions */
extern volatile sig_atomic_t g_signal;
void handle_sigint(int sig);
void catch_sigint(int sigint);
void setup_signal_handler(t_data *data, void (*handler)(int));
void setup_signal_mode(t_data *data, int interactive);

/* Lexer functions */
void	parse_line(t_data *data);
void	parse_tokens(t_data *data);
void	parse_token(t_data *data, char **start, char **end, bool *single_or_double);
t_token	*create_token(char *str, bool quote, bool single_or_double);
void	add_token_to_end(t_token **head, t_token *new_token);
void	set_token_type(t_token *token);
void	skip_spaces(char **line);
char	*parse_regular_token(char **start, char **end);
char	*parse_quoted_token(char **start, char **end, bool *single_or_double);
void	join_adjacent_words(t_token **head);

// Parser functions
void	process_tokens(t_data *data);
void	expand_tokens(t_data *data);	
void	process_redirection(t_data *data, t_token **token);
char	*expand(t_data *data, char *word);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	*get_env_value(t_data *data, char *name);

// OLLIE
// Executing functions
void	run(t_data *data);
void	builtin(t_data *data, t_exec *exec);
void	command(t_data *data, t_exec *exec);
void	clean_exec(t_data *data);
int		fork1(t_data *data);
void	open_pipe_exec(t_data *data, t_exec *exec);
void	close_pipe_exec(t_data *data, t_exec *exec);
void	reroute(t_exec *exec);
void	safe_close(int fd);
void	check_exit_status(t_data *data, int exit_status);
size_t	exec_len(t_exec *exec);

// Environment functions
t_envlist	*parse_env(t_data *data, char **ev);
size_t	env_len(t_envlist *env);
char	*expand(t_data *data, char *s);
void	sort_env(t_envlist *list);
t_envlist	*dup_env(t_envlist *list);


// Path functions
void	update_path(t_data *data);
void	parse_path(t_data *data);
void	free_path(t_data *data);
void	add_slash(char **path);
void	set_path(t_data *data, t_exec *exec);
void	set_cmd_path(t_data *data, t_exec *exec);

// Builtins
void		echo(t_data *data, t_exec *exec);
void		cd(t_data *data, t_exec *exec);
void		cd_home(t_data *data, t_exec *exec);
char		*get_home(t_data *data);
void		pwd(t_data *data, t_exec *exec);
void		update_pwd(t_data *data);
t_envlist	*get_pwd(t_data *data);
t_envlist	*get_oldpwd(t_data *data);
void		ft_exit(t_data *data, t_exec *exec);
void		export(t_data *data, t_exec *exec);

char		**create_argv(t_data *data, t_token *token);
size_t		argv_size(t_token *token);
void		init_exec_data(t_data *data);


// HereDoc
char	*random_name(void);
char	*here_doc(t_data *data, char *l);
// General utils
void	bruh(t_data *data, char *s, int status);
size_t	ft_arrlen(char **arr);
// Free functions
void	free_tokens(t_data *data);
void	free_old_token(t_token *token);
void	free_env_list(t_envlist *env);
void	free_arr(char ***arr);
void	free_token_node(t_token **token);

// Debug functions
void	print_token(t_token *token);
void	print_tokens(t_token *token);
void	print_arr(char **arr);
void	print_exec(t_exec *exec);
void	print_env(t_data *data);

#endif
