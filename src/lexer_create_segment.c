/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_create_segment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:37:08 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/16 18:45:16 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_segments(t_token *token)
{
	size_t		total_len;
	char		*joined;
	t_segment	*seg;

	total_len = 0;
	seg = token->segments;
	while (seg)
	{
		total_len += ft_strlen(seg->text);
		seg = seg->next;
	}
	joined = ft_calloc(total_len + 1, sizeof(char));
	if (!joined)
		return (NULL);
	seg = token->segments;
	while (seg)
	{
		ft_strlcat(joined, seg->text, total_len + 1);
		seg = seg->next;
	}
	return (joined);
}

void	add_segment_to_token(t_token *token, t_segment *seg)
{
	t_segment	*curr;

	curr = token->segments;
	if (!curr)
	{
		token->segments = seg;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = seg;
}

int	append_char_to_segment(t_segment *seg, char c)
{
	size_t	old_len;
	char	*new_text;

	old_len = ft_strlen(seg->text);
	new_text = ft_realloc(seg->text, old_len, old_len + 2);
	if (!new_text)
		return (-1);
	seg->text = new_text;
	seg->text[old_len] = c;
	seg->text[old_len + 1] = '\0';
	return (0);
}

t_segment	*create_segment(bool single_quoted, bool double_quoted)
{
	t_segment	*seg;

	seg = ft_calloc(1, sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->text = ft_calloc(1, sizeof(char));
	if (!seg->text)
		return (free(seg), NULL);
	seg->single_quoted = single_quoted;
	seg->double_quoted = double_quoted;
	seg->next = NULL;
	return (seg);
}
