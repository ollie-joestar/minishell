/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:51:14 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/27 14:51:58 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_dont_expand_check(t_token *filename_token)
{
	t_segment	*seg;

	seg = filename_token->segments;
	while (seg)
	{
		if (seg->single_quoted || seg->double_quoted)
			return (1);
		seg = seg->next;
	}
	return (0);
}

t_token	*handle_heredoc(t_data *data, t_token *redirection_token,
						t_token *filename_token)
{
	int			dont_expand;
	char		*temp_word;
	char		*here_result;

	dont_expand = heredoc_dont_expand_check(filename_token);
	temp_word = join_segments(filename_token);
	if (!temp_word)
		bruh(data, "Failed to join filename segments for HEREDOC", 2);
	here_result = here_doc(data, temp_word, dont_expand);
	ft_free(&temp_word);
	free_token_node(&filename_token);
	filename_token = create_token_for_string(here_result);
	ft_free(&here_result);
	if (!filename_token)
		return (NULL);
	filename_token->type = HEREDOC;
	filename_token->next = redirection_token->next;
	return (filename_token);
}
