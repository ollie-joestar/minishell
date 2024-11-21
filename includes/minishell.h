/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/21 23:01:49 by hanjkim          ###   ########.fr       */
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
	int					type; // WORD | PIPE | INPUT | HEREDOC | REPLACE | APPEND
	char				*word;

	struct s_lex_token	*left; //changed to left and right for better recognition of command order (like official doc says)
	struct s_lex_token	*right;
}		t_token;

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
	pid_t				pid; // to store last child process id
	t_exec				*exec; // to store the current command data
	char				**ev; // to store the environment variables
	
	t_envlist			*env; // to store the environment variables in a linked list
	char				**path; // to store the path variable after splitting
	int					status; // to store the exit status of the last command
	struct sigaction	sa; // to store the signal action

	char				*line; //lineread (add to history and free after execution)
	t_token				*token; // to store the list of tokenized commands
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

// Parser functions
int		find_start_index(int current_index);
int		find_end_index(t_token *token, int start_index, char quote);
void	read_single_quotes(char **buffer, t_token *token, int *i);
void	read_double_quotes(t_data *data, t_token *token, char **buffer, int *i);
void	check_for_needed_expansion(t_data *data);
t_token *expand_token(t_data *data, char *word);
void	insert_expanded_tokens(t_token *expanded_tokens, t_token *old_token);
void	update_token_links(t_token *fntok, t_token *lntok, t_token *old_token);
char	**expand_token_to_words(t_data *data, char *word);
int		requires_expansion(char *word);
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
