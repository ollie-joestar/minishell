/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/14 18:13:08 by hanjkim          ###   ########.fr       */
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

# define INTERPRET 040
# define NO_VAR 0200
# define TO_SPLIT CHAR_MAX
// pipes
# define RD 0
# define WR 1
// quotes
# define SQ '\''
# define DQ '\"'
// Token types
# define WORD 0
# define PIPE 1
# define INPUT 2
# define HEREDOC 04
# define REPLACE 010
# define APPEND 020

typedef struct s_lex_token
{
	int					type; // WORD | PIPE | INPUT | HEREDOC | REPLACE | APPEND
	char				*word;

	struct s_lex_token	*left; //changed to left and right for better recognition of command order (like official doc says)
	struct s_lex_token	*right;
}		t_lex_token;

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
	t_lex_token			*token; // to store the list of tokenized commands
}		t_data;

/* Lexer functions */
t_lex_token	*create_token(void);
void		init_tokens(t_data *data);
void		check_token_type(t_lex_token *token);
void		process_token(t_data *data, t_lex_token **token, int type);
void		tokenization(t_data *data);
/*t_token	*create_token(int type, char *str);*/
/*t_token	*tokenize(t_lexer_context *lexer_ctx);*/
/*int		add_token(t_lexer_context *lexer_ctx, char **start);*/
/*void		add_token_to_list(t_lexer_context *lexer_ctx, t_token *new_token);*/
/*void		free_tokens(t_lexer_context *lexer_ctx);*/
/*int		identify_token_type(t_lexer_context *lexer_ctx, char **start, char **end);*/
void		skip_whitespace(char **input);
int			identify_pipe(char **start, char **end);
int			identify_single_quotes(char **start, char **end);
int			identify_double_quotes(char **start, char **end);
void		ft_strncpy(char	*dest, const char *str, size_t n);
char		*ft_strndup(const char *s, size_t n);
char		*token_end(char *start);
void		reset_end(char *start, char **end, char *ptr, char *tkn_end);

// OLLIE

// Executing functions
void	runcmd(t_data *data);
/*void	run_exec(t_data *data);*/
void	run_builtin(t_data *data, t_exec *exec);
void	clean_exec(t_data *data);
int		fork1(t_data *data);
void	reroute(t_data *data);
void	reset_stds(int	stdin_copy, int	stdout_copy);

// Environment functions
void	parse_env(t_data *data, char **ev);
size_t	env_len(t_envlist *env);
char	*expand(t_data *data, char *s);

// Path functions
void	update_path(t_data *data);
void	parse_path(t_data *data);
void	free_path(t_data *data);
void	add_slash(char **path);

// Builtins
void		echo(t_data *data, t_exec *exec);
void		cd(t_data *data, t_exec *exec);
void		cd_home(t_data *data, t_exec *exec);
char		*get_home(t_data *data);
void		pwd(t_data *data, t_exec *exec);
void		update_pwd(t_data *data);
t_envlist	*get_pwd(t_data *data);
t_envlist	*get_oldpwd(t_data *data);

char		**create_argv(t_data *data, t_lex_token *token);
size_t		argv_size(t_lex_token *token);
void		init_exec_data(t_data *data);

// HereDoc
char	*random_name(void);
char	*here_doc(t_data *data, char *l);
// General utils
void	bruh(t_data *data, char *s, int status);
size_t	ft_arrlen(char **arr);
// Free functions
void	free_tokens(t_data *data);
void	free_env_list(t_data *data);
void	free_arr(char **arr);
void	free_token_node(t_lex_token **token);

#endif
