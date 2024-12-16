/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:07:19 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/16 17:50:33 by hanjkim          ###   ########.fr       */
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

typedef struct s_segment {
    char              *text;
    bool              single_quoted;
    bool              double_quoted;
    struct s_segment  *next;
} t_segment;

typedef struct s_token {
	char		*word;
	t_segment       *segments;
	t_token_type    type;
	struct s_token  *next;
	struct s_token  *prev;
}		t_token;

typedef struct s_split_vars
{
	char	**words;
	t_token *new_head;
	t_token *new_tail;
	t_token *new_token;
	int	 i;
}		t_split_vars;

typedef struct s_replace
{
	t_token *original;
	t_token *new_head;
	struct s_replace *next;
}		t_replace;

typedef struct s_expander {
	char	*result;
	size_t  result_size;
	size_t  old_result_size;
	size_t  index_word;	// index of the current character in the word
	size_t  index_res;	// index of the current character in the result
}		t_expander;

typedef struct s_input {
	int		type; // HERE_DOC | FILE
	char		*file;
	struct s_input	*next;
	struct s_input	*prev;
}			t_input;

typedef struct s_output {
	int		type; // REPLACE | APPEND
	char	*file;
}			t_output;

typedef struct s_envlist {
	char		*name;
	char			*value;
	struct s_envlist	*next;
	struct s_envlist	*prev;
}				t_envlist;

typedef struct s_exec {
	int			type; // BUILTIN | CMD
	t_input		*in; // linked list of input files
	t_output	*out; // linked list of output files
	int			piped; // 1 if the command is piped
	int			pipe[2]; // pipe file descriptors
	char		*cmd; // full path to the command
	char		**av;
	struct s_exec   *prev;
	struct s_exec   *next;
}			t_exec;


typedef struct s_data
{
    pid_t           pid;
    t_exec          *exec;   
    char            **ev;     
    t_envlist       *env;    
    char            **path;   
    int             status;
    struct sigaction sa;
    char            *line;    
    t_token         *token;
    t_replace       *replacements;
    t_expander      *expander;
    size_t          current_size; 
    char            *buffer;
}   t_data;

/* Signal functions */
extern volatile sig_atomic_t g_signal;
void	catch_sigint(int sigint);
void	setup_signal_handler(t_data *data, void (*handler)(int));
void	setup_signal_mode(t_data *data, int interactive);

/* Lexer functions */
void	parse_line(t_data *data);
void	parse_tokens(t_data *data);
void	parse_and_create_token(t_data *data, char *input, int *start, int *end);
t_token	*create_token(char *str, bool quote, bool single_or_double);
void	add_token_to_end(t_token **head, t_token *new_token);
void	set_token_type(t_token *token);
void	skip_spaces(char *input, int *i);
int	process_current_c(char *input, int *i, t_data *data);
int	process_quote_part(char *input, int *i, t_data *data);
int	append_char(char **buffer, size_t *current_size, char c);
t_token	*create_token_from_string(char *str);
t_token	*create_empty_token(void);
t_segment	*create_segment(bool single_quoted, bool double_quoted);
void	add_segment_to_token(t_token *token, t_segment *seg);
void	finalize_tokens(t_token *token_list);
t_token *parse_word_token(char *input, int *start, t_data *data);

/* Lexer utils */
bool	should_split_token(t_token *token);
void	add_replace(t_data *data, t_token *o_token, t_token *new_head);
void	replace_token(t_data *data, t_token *original_token, t_token *new_tokens_head);
void	replace_tokens(t_data *data);
void	split_tokens(t_data *data);
t_token	*split_token(t_token *original_token, t_data *data);
char	**get_split_words(t_token *original_token, t_data *data);
void	make_split_tokens(t_split_vars *vars, t_token *o_token, t_data *data);
char	*join_segments(t_token *token);

// Parser functions
void	process_tokens(t_data *data);
void	expand_tokens(t_data *data);	
void	process_redirection(t_data *data, t_token **token);
char	*expand(t_data *data, char *word);
int	handle_dollar_exp(t_data *data, t_expander *expander);
int	handle_variable_exp(t_data *data, char *word, t_expander *expander);
int	handle_regular_char(char c, t_expander *expander);
int	handle_special_dollar(t_data *data, char *word, t_expander *expander);
t_token	*handle_heredoc(t_data *data, t_token *redirection_token,
			t_token *filename_token);

// Parser utils
void	*ft_realloc(void *str, size_t old_size, size_t new_size);
char	*get_env_value(t_data *data, char *name);
char	*initialize_expander(t_expander *expander, char *word);
int	resize_result(t_expander *expander, size_t required_size);

// Syntax checker
void	unexpected_token(t_data *data, char *str);
bool	double_pipe(t_token *token);
bool	missing_file(t_token *token);
bool	pipe_in_front(t_token *token);
bool	valid_syntax(t_data *data, t_token *token);
bool	is_redirection(t_token *token);
bool unexpected_token_with_join(t_data *data, t_token *token);

// OLLIE
// Executing functions
void	run(t_data *data);
void	builtin(t_data *data, t_exec *exec);
void	command(t_data *data, t_exec *exec);
void	clean_exec(t_data *data);
int		fork1(t_data *data);
void	open_pipe_exec(t_data *data, t_exec *exec);
void	close_pipe_exec(t_data *data, t_exec *exec);
void	reroute(t_data *data, t_exec *exec);
void	safe_close(int fd);
void	check_exit_status(t_data *data, int exit_status);
size_t	exec_len(t_exec *exec);
int		exec_has_cmd(t_exec *exec);

// Environment functions
t_envlist   *parse_env(t_data *data, char **ev);
size_t		env_len(t_envlist *env);
char		*expand(t_data *data, char *s);
void		sort_env(t_envlist *list);
t_envlist   *dup_env(t_envlist *list);


// Path functions
void	update_path(t_data *data);
void	parse_path(t_data *data);
void	free_path(t_data *data);
void	set_path(t_data *data, t_exec *exec);
void	set_cmd_path(t_data *data, t_exec *exec);

// Builtins
void		echo(t_data *data, t_exec *exec);
void		cd(t_data *data, t_exec *exec);
void		cd_home(t_data *data, t_exec *exec);
char		*get_home(t_data *data);
void		pwd(t_data *data, t_exec *exec);
void		update_pwd(t_data *data);
t_envlist   *get_pwd(t_data *data);
t_envlist   *get_oldpwd(t_data *data);
void		ft_exit(t_data *data, t_exec *exec);
void		export(t_data *data, t_exec *exec);
void		unset(t_data *data, t_exec *exec);

char		**create_argv(t_data *data, t_token *token);
size_t		argv_size(t_token *token);
void		init_exec_data(t_data *data);

// HereDoc
char	*random_name(void);
char	*here_doc(t_data *data, char *l, int to_expand);
void	expand_var_in_str(t_data *data, char **str);
// General utils
void	bruh(t_data *data, char *s, int status);
size_t	ft_arrlen(char **arr);
// Free functions
void	free_tokens(t_data *data);
void	free_old_token(t_token *token);
void	free_env_list(t_envlist *env);
void	free_env_node(t_envlist *env);
void	free_arr(char ***arr);
void	free_token_node(t_token **token);

// Debug functions
void	print_token(t_token *token);
void	print_tokens(t_token *token);
void	print_arr(char **arr);
void	print_exec(t_exec *exec);
void	print_env(t_data *data);

#endif
