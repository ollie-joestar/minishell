/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/24 23:47:28 by hanjkim          ###   ########.fr       */
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

/*# define INTERPRET 040*/
/*# define NO_VAR 0200*/
/*# define TO_SPLIT CHAR_MAX*/
// pipes
# define RD 0
# define WR 1
// quotes
# define SQ '\''
# define DQ '\"'
# define SLASH '\\'
# define DOLLAR '$'
// Token types
# define WORD 0
# define PIPE 1
# define INPUT 2
# define HEREDOC 3
# define REPLACE 4
# define APPEND 5

typedef struct s_lex_token
{
	int			type;
	char			*word;
	struct s_lex_token	*left;
	struct s_lex_token	*right;
}		t_token;

typedef struct s_merge_state {
	t_token	*start_token;
	t_token	*end_token;
	char	*combined_word;
	int	is_inside_quotes;
	char	quote_char;
} t_merge;

typedef struct s_split_quotes {
	t_token *prefix;
	t_token *quoted;
	t_token *suffix;
	char	*start_quote;
	char	*end_quote;
	size_t	prefix_len;
	size_t	quoted_len;
	size_t	suffix_len;
	char	*prefix_str;
	char	*quoted_str;
	char	*suffix_str;
} t_split;

typedef struct s_input {
	int				type; // HERE_DOC | FILE
	char			*file;
	struct s_input	*next;
	struct s_input	*prev;
}			t_input;

typedef struct s_output {
	int		type; // REPLACE | APPEND
	char	*file;
}			t_output;

typedef struct s_envlist {
	char				*name;
	char				*value;
	struct s_envlist	*next;
	struct s_envlist	*prev;
}			t_envlist;

typedef struct s_exec {
	int				type; // BUILTIN | CMD
	t_input			*in; // linked list of input files
	t_output		*out; // linked list of output files
	int				piped; // 1 if the command is piped
	int				pipe[2]; // pipe file descriptors

	char			*cmd; // full path to the command
	char			**av;

	struct s_exec	*prev;
	struct s_exec	*next;
}			t_exec;


typedef struct s_data
{
	pid_t			pid; // to store last child process id
	t_exec			*exec; // to store the current command data
	char			**ev; // to store the environment variables
	
	t_envlist		*env; // to store the environment variables in a linked list
	char			**path; // to store the path variable after splitting
	int			status; // to store the exit status of the last command
	struct sigaction	sa; // to store the signal action
	char			*line; //lineread (add to history and free after execution)
	/*char			*joined_line; // to store the joined line after tokenization*/
	t_token			*token; // to store the list of tokenized commands
}		t_data;

/* Signal functions */
extern volatile sig_atomic_t g_signal;
void handle_sigint(int sig);
void catch_sigint(int sigint);
void setup_signal_handler(t_data *data, void (*handler)(int));
void setup_signal_mode(t_data *data, int interactive);

/* Lexer functions */
t_token		*create_token(void);
t_token		*init_tokens(t_data *data, char **av);
void		set_token_type(t_token *token);
void		process_token(t_data *data, t_token **token, int type);
void		tokenization(t_data *data);
void		skip_whitespace(char **input);
int			identify_pipe(char **start, char **end);
char		*token_end(char *start);
void		reset_end(char *start, char **end, char *ptr, char *tkn_end);
void		parse_line(t_data *data);
void		merge_quoted_tokens(t_data *data);
void		handle_quoted_tokens(t_data *data);
// Token utils
void		free_token_slice(t_token *first, t_token *last);
t_token		*get_first_token(t_token *token);
t_token		*get_last_token(t_token *token);
t_token		*get_first_split_token(t_split *tokens);
t_token		*get_last_split_token(t_split *tokens);

// Parser functions
void	split_quoted_token(t_data *data);
void	adjust_links(t_token *token, t_token *left, t_token *right);
void	adjust_prefix_links(t_token *prefix, t_token *left, t_token *right, t_split *tokens);
void	adjust_quoted_links(t_token *quoted, t_token *left, t_token *right, t_split *tokens);
void	adjust_suffix_links(t_token *suffix, t_token *left, t_token *right, t_split *tokens);
t_token *update_pointer(t_split *tokens);
void	expand_token(t_data *data, t_token *token);
void	insert_expanded_tokens(t_token *expanded_tokens, t_token *old_token);
void	insert_token(t_token *fntok, t_token *lntok, t_token *old_token);
char	*process_word_expansion(t_data *data, char *word);
char	*process_quotes(t_data *data,char *expanded_word, char *word);
void	process_quotes_2(t_data *data);
void	process_env_variable(t_data *data, char **buffer, int *index);
size_t	var_len(char *name);
void	expand_vars_in_token(t_data *data, t_token *token, int i);
void	expand_vars_in_token_list(t_data *data, t_token *token);
void	expand_dquote(t_data *data, t_token *token, char *word);
void	expand_squote(t_data *data, t_token *token, char *word);

//Parser utils
char	*slice(char *word, size_t start, size_t length);
void	update_data_token(t_data *data, t_token *left, t_token *first_new);

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
void	parse_env(t_data *data, char **ev);
size_t	env_len(t_envlist *env);
char	*expand(t_data *data, char *s);

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

char		**create_argv(t_data *data, t_token *token);
size_t		argv_size(t_token *token);
void		init_exec_data(t_data *data);


// HereDoc
char	*random_name(void);
char	*here_doc(t_data *data, char *l);
// General utils
void	bruh(t_data *data, char *s, int status);
size_t	ft_arrlen(char **arr);
char	*ft_strjoin_and_free(char *s1, char *s2);
// Free functions
void	free_tokens(t_data *data);
void	free_old_token(t_token *token);
void	free_env_list(t_data *data);
void	free_arr(char ***arr);
void	free_token_node(t_token **token);

// Debug functions
void	print_token(t_token *token);
void	print_tokens(t_token *token);
void	print_arr(char **arr);
void	print_exec(t_exec *exec);
void	print_env(t_data *data);

#endif
