/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/07 16:05:19 by oohnivch         ###   ########.fr       */
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

/*redir *here_doc() */
/*{*/
/*	int flag_type; // 0 = expand, 1 = no expand*/
/*	// if lim = expand*/
/*	// if "lim" = not expand*/
/**/
/*};*/



/*HANJU*/
typedef struct s_lexer_context
{
	t_token		*tokens;
	t_token		*last_token;
	char		*line;
	size_t		len;
}		t_lexer_context;

//
// 
// GOOD STUFF KIUNDA BUT STUKKL BAD FOR NOW
//
//
//
typedef struct s_input {
	int				flag; // HERE_DOC | FILE
	char			*file_name;
	struct s_input	*next;
	struct s_input	*prev;
}			t_input;

typedef struct s_output {
	int		type; // REPLACE | APPEND
	char	*file_name;
}			t_output;

typedef struct s_redir {
	t_input		*input;
	t_output	*output;
}			t_redir;

typedef struct s_token
{
	int				type; 
	struct s_token	*prev;
	struct s_token	*next;
	char			*content;
}		t_token;

typedef struct s_exec_data {
	int					type; // 0 = builtin, 1 = cmd;
	t_redir				*redir;
	int					pipe[2];
	struct exec_data	*prev;
	struct exec_data	*next;
	char				**argv;
}			t_exec_data;

typedef struct s_data
{
	t_exec_data	*exec_data;
	char		**ev;
	/*t_token		*token;*/
}				t_data;


//
//
//
// GOOD STUFF KIUNDA BUT STUKKL BAD FOR NOW END
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
/*t_cmd	*init_execcmd(void);*/
/*t_cmd	*init_redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);*/
/*t_cmd	*init_pipecmd(t_cmd *left, t_cmd *right);*/
/*t_cmd	*init_listcmd(t_cmd *left, t_cmd *right);*/
/*t_cmd	*init_backcmd(t_cmd *subcmd);*/


void			runcmd(t_data *data);
/*void			exec_exec(t_data *data, t_execcmd *ecmd);*/
/*void			exec_redir(t_data *data, t_redircmd *rcmd);*/
/*void			exec_pipe(t_data *data, t_pipecmd *pcmd);*/
/*void			exec_list(t_data *data, t_listcmd *lcmd);*/
/*void			exec_back(t_data *data, t_backcmd *bcmd);*/
void			bruh(t_data *data, char *s, int status);
int				fork1(t_data *data);

#endif
