/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:47:48 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/18 21:10:26 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*process_double_op(char *input, int *i, int *start, t_data *data)
{
	t_token		*token;
	t_segment	*seg;
	char		*op_str;

	token = create_empty_token();
	seg = create_segment(false, false);
	if (!token || !seg)
		return (free(token), free(seg), free_tokens(data), NULL);
	op_str = ft_substr(input, *i, 2);
	if (!op_str)
		return (free_segment(&seg), free_token_node(&token), NULL);
	ft_free(&seg->text);
	seg->text = op_str;
	if (input[*i] == '<')
		token->type = HEREDOC;
	else
		token->type = APPEND;
	(*i) += 2;
	*start = *i;
	add_segment_to_token(token, seg);
	return (token);
}

t_token	*process_single_op(char *input, int *i, int *start, t_data *data)
{
	t_token		*token;
	t_segment	*seg;
	char		*op_str;

	token = create_empty_token();
	seg = create_segment(false, false);
	if (!token || !seg)
		return (free(token), free(seg), free_tokens(data), NULL);
	op_str = ft_substr(input, *i, 1);
	if (!op_str)
		return (free_segment(&seg), free_token_node(&token), NULL);
	ft_free(&seg->text);
	seg->text = op_str;
	if (input[*i] == '<')
		token->type = INPUT;
	else if (input[*i] == '>')
		token->type = REPLACE;
	else
		token->type = PIPE;
	(*i)++;
	*start = *i;
	add_segment_to_token(token, seg);
	return (token);
}

t_token	*process_operator(char *input, int *i, int *start, t_data *data)
{
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
		return (process_double_op(input, i, start, data));
	else
		return (process_single_op(input, i, start, data));
}
