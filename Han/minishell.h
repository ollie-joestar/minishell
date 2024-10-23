/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:47 by oohnivch          #+#    #+#             */
/*   Updated: 2024/10/23 15:07:23 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/includes/libft.h"
/* Token types */
# define END 01
# define IN_R 02
# define HEREDOC 04
# define CMD 010
# define PIPE 020
# define INTERPRET 040
# define NO_VAR 0200
# define TO_SPLIT CHAR_MAX

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

/* Lexer functions */
t_token	*create_token(int type, char *str);
t_token	*tokenize(t_lexer_context *lexer_ctx);
int	add_token(t_lexer_context *lexer_ctx, char **start);
void	add_token_to_list(t_lexer_context *lexer_ctx, t_token *new_token);
void	free_tokens(t_lexer_context *lexer_ctx);
void	skip_whitespace(char **input);
int	identify_token_type(t_lexer_context *lexer_ctx, char **start, char **end);
int	identify_pipe(char **start, char **end);
int	identify_single_quotes(char **start, char **end);
int	identify_double_quotes(char **start, char **end);
void	ft_strncpy(char	*dest, const char *str, size_t n);
char	*ft_strndup(const char *s, size_t n);
char	*token_end(char *start);
void	reset_end(char *start, char **end, char *ptr, char *tkn_end);

#endif
