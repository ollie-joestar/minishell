/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 16:54:04 by oohnivch         ###   ########.fr       */
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
# include <errno.h>

//TOKEN TYPES
//HERE_DOC
//input
//pipe
//output
//words


# define FILE 02
# define HEREDOC 04
# define BUILTIN 69
# define CMD 420
# define REPLACE 010
# define APPEND 020
/*# define PIPE 020*/
# define INTERPRET 040
# define NO_VAR 0200
# define TO_SPLIT CHAR_MAX
# define RD 0
# define WR 1

/*redir *here_doc() */
/*{*/
/*	int flag_type; // 0 = expand, 1 = no expand*/
/*	// if lim = expand*/
/*	// if "lim" = not expand*/
/**/
/*};*/



/*HANJU*/
//
// 
// GOOD STUFF KINDA BUT STILL BAD FOR NOW
//
//
//
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

typedef struct s_redir {
	t_input		*in;
	t_output	*out;
}			t_redir;

typedef struct s_token
{
	int				type; 
	struct s_token	*prev;
	struct s_token	*next;
	char			*content;
}		t_token;

//???????
typedef struct s_lexer_context
{
	t_token		*tokens;
	t_token		*last_token;
	char		*line;
	size_t		len;
}		t_lexer_context;

typedef struct s_exec {
	int				type; // BUILTIN | CMD
	t_redir			*redir;
	int				pipe[2];

	char			*cmd;
	char			**av;

	struct s_exec	*prev;
	struct s_exec	*next;
}			t_exec;

typedef struct s_data
{
	pid_t		pid;
	t_exec		*exec;
	char		**ev;
	char		**path;
	int			status;
	
	struct sigaction	sa; //newly added
	t_lex_token		*token; //newly added
	t_lex_token		*last_token; //newly added
	t_parse_token	*list; //newly added
	t_parse_token	*curr_token; //newly added
}				t_data;

//
//
//
// GOOD STUFF KINDA BUT STILL BAD FOR NOW END
//
//
//

/* Lexer functions */
t_token	*create_token(int type, char *str);
t_token	*tokenize(t_lexer_context *lexer_ctx);
int		add_token(t_lexer_context *lexer_ctx, char **start);
void	add_token_to_list(t_lexer_context *lexer_ctx, t_token *new_token);
void	free_tokens(t_lexer_context *lexer_ctx);
void	skip_whitespace(char **input);
int		identify_token_type(t_lexer_context *lexer_ctx, char **start, char **end);
int		identify_pipe(char **start, char **end);
int		identify_single_quotes(char **start, char **end);
int		identify_double_quotes(char **start, char **end);
void	ft_strncpy(char	*dest, const char *str, size_t n);
char	*ft_strndup(const char *s, size_t n);
char	*token_end(char *start);
void	reset_end(char *start, char **end, char *ptr, char *tkn_end);

// OLLIE
void	reroute(t_data *data);
void	runcmd(t_data *data);
void	bruh(t_data *data, char *s, int status);
int		fork1(t_data *data);
void	run_exec(t_data *data);
void	run_builtin(t_data *data);
void	clean_exec(t_data *data);

#endif
