/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 15:22:11 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>


# define FILE 02
# define HEREDOC 04
# define BUILTIN 69
# define CMD 420
# define REPLACE 010
# define APPEND 020
# define INTERPRET 040
# define NO_VAR 0200
# define TO_SPLIT CHAR_MAX
# define RD 0
# define WR 1

typedef struct s_lex_token
{
	int					type; // word, pipe, redirect, etc.
	char				*word;

	struct s_lex_token	*left; //changed to left and right for better recognition of command order (like official doc says)
	struct s_lex_token	*right;
}		t_lex_token;

typedef struct s_parse_token 
{
	int					type;
	char				**content; //Double pointer to iterate over command flags during parsing
	//
	struct s_parse_token	*next;
	struct s_parse_token	*prev;
}		t_parse_token;

typedef struct s_input {
	int				flag; // HERE_DOC | FILE
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
	t_input			*input; // linked list of input files
	t_output		*output; // linked list of output files
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
	t_lex_token			*last_token; // to point to the last token in the list
	t_parse_token		*list; // to store the list of parsed commands 
	t_parse_token		*curr_token; //newly added
}		t_data;

//
//
//
// GOOD STUFF KINDA BUT STILL BAD FOR NOW END
//
//
//

/* Lexer functions */
/*t_token	*create_token(int type, char *str);*/
/*t_token	*tokenize(t_lexer_context *lexer_ctx);*/
/*int		add_token(t_lexer_context *lexer_ctx, char **start);*/
/*void	add_token_to_list(t_lexer_context *lexer_ctx, t_token *new_token);*/
/*void	free_tokens(t_lexer_context *lexer_ctx);*/
/*int		identify_token_type(t_lexer_context *lexer_ctx, char **start, char **end);*/
void	skip_whitespace(char **input);
int		identify_pipe(char **start, char **end);
int		identify_single_quotes(char **start, char **end);
int		identify_double_quotes(char **start, char **end);
void	ft_strncpy(char	*dest, const char *str, size_t n);
char	*ft_strndup(const char *s, size_t n);
char	*token_end(char *start);
void	reset_end(char *start, char **end, char *ptr, char *tkn_end);
void	tokenization(t_data *data);

// OLLIE
void	reset_stds(int	stdin_copy, int	stdout_copy);
void	reroute(t_data *data);
void	runcmd(t_data *data);
void	bruh(t_data *data, char *s, int status);
int		fork1(t_data *data);
void	run_exec(t_data *data);
void	run_builtin(t_data *data);
void	clean_exec(t_data *data);

#endif
