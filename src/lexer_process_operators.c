/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_operators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:59:03 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/16 17:45:55 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *process_double_op(char *input, int *i, int *start, t_data *data)
{
    t_token     *token;
    t_segment   *seg;

    token = create_empty_token();
    seg = create_segment(false, false);
    if (!token || !seg)
        return (free(token), free(seg), free_tokens(data), NULL);
    if (append_char_to_segment(seg, input[*i]) == -1
        || append_char_to_segment(seg, input[*i + 1]) == -1)
    {
        free_segment(&seg);
        return (free_token_node(&token), NULL);
    }
    if (input[*i] == '<')
        token->type = HEREDOC;
    else
        token->type = APPEND;
    (*i) += 2;
    *start = *i;
    add_segment_to_token(token, seg);
    return (token);
}

t_token *process_single_op(char *input, int *i, int *start, t_data *data)
{
    t_token     *token;
    t_segment   *seg;

    token = create_empty_token();
    seg = create_segment(false, false);
    if (!token || !seg)
        bruh(data, "Failed to allocate memory", 1);
    if (append_char_to_segment(seg, input[*i]) == -1)
        bruh(data, "Failed to append chars", 1);
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

t_token *process_operator(char *input, int *i, int *start, t_data *data)
{
    if ((input[*i] == '<' && input[*i + 1] == '<')
        || (input[*i] == '>' && input[*i + 1] == '>'))
        return (process_double_op(input, i, start, data));
    else
        return (process_single_op(input, i, start, data));
}
