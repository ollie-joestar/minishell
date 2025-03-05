/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_create_segment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:37:08 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/05 23:46:04 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Join all segments of a token into a single string
char	*join_segments(t_token *token)
{
	size_t		total_len;
	char		*joined;
	t_segment	*seg;

	total_len = 0;
	seg = token->segments;
	while (seg)
	{
		if (seg->text)
			total_len += ft_strlen(seg->text);
		else
			total_len += 0;
		seg = seg->next;
	}
	joined = ft_calloc(total_len + 1, sizeof(char));
	if (!joined)
		return (NULL);
	seg = token->segments;
	while (seg)
	{
		if (seg->text)
			ft_strlcat(joined, seg->text, total_len + 1);
		seg = seg->next;
	}
	return (joined);
}

// Add a string segment to a token's segment placeholder
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

// Create a new segment with the given quote markers
t_segment	*create_segment(bool single_quoted, bool double_quoted)
{
	t_segment	*seg;

	seg = ft_calloc(1, sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->text = NULL;
	seg->single_quoted = single_quoted;
	seg->double_quoted = double_quoted;
	seg->next = NULL;
	return (seg);
}
