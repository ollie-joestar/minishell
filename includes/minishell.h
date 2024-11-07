/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/07 12:10:24 by oohnivch         ###   ########.fr       */
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

/* Token types */
# define END 01
# define IN_R 02
# define HEREDOC 04
# define CMD 010
/*# define PIPE 020*/
# define INTERPRET 040
# define NO_VAR 0200
# define TO_SPLIT CHAR_MAX

/*Ollie start*/
# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5
# define MAXARGS 128

typedef struct	s_cmd {
	int type;
}		t_cmd;

typedef struct	s_execcmd {
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
}		t_execcmd;

typedef struct	s_redircmd {
	int type;
	struct s_cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
}		t_redircmd;

typedef struct	s_pipecmd {
	int type;
	struct s_cmd *left;
	struct s_cmd *right;
}		t_pipecmd;

typedef struct	s_listcmd {
	int type;
	struct s_cmd *left;
	struct s_cmd *right;
}		t_listcmd;

typedef struct	s_backcmd {
	int type;
	struct s_cmd *cmd;
}		t_backcmd;

/*Ollie end*/




/*HANJU*/
typedef struct s_token
{
	int		type;
	struct s_token	*right;
	struct s_token	*left;
	char		*str;
}		t_token;

typedef struct s_lexer_context
{
	t_token		*tokens;
	t_token		*last_token;
	char		*line;
	size_t		len;
}		t_lexer_context;

typedef struct s_data
{
	t_token		*token;
}				t_data;

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
t_cmd	*init_execcmd(void);
t_cmd	*init_redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);
t_cmd	*init_pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*init_listcmd(t_cmd *left, t_cmd *right);
t_cmd	*init_backcmd(t_cmd *subcmd);

void			runcmd(t_data *data, t_cmd *cmd);
void			exec_exec(t_data *data, t_execcmd *ecmd);
void			exec_redir(t_data *data, t_redircmd *rcmd);
void			exec_pipe(t_data *data, t_pipecmd *pcmd);
void			exec_list(t_data *data, t_listcmd *lcmd);
void			exec_back(t_data *data, t_backcmd *bcmd);
void			bruh(t_data *data, char *s, int status);
int				fork1(t_data *data);

#endif
