/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:46:04 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/18 16:22:42 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_segment(t_data *data, t_segment *seg, t_token *token)
{
	char	*expanded;

	(void)token;
	if (seg->single_quoted)
		return (ft_strdup(seg->text));
	expanded = expand(data, seg->text);
	if (!expanded)
		return (ft_strdup(""));
	if (!seg->single_quoted && !seg->double_quoted && seg->text[0] == '$'
		&& expanded[0] == '\0')
		seg->env_not_found = true;
	return (expanded);
}

int	process_token_redirection(t_data *data, t_token **token)
{
	if ((*token)->type != WORD && (*token)->type != PIPE)
	{
		process_redirection(data, token);
		if (data->ambig_redir)
		{
			free_tokens(data);
			return (1);
		}
	}
	return (0);
}

void	expand_tokens(t_data *data)
{
	t_token		*current;
	char		*expanded;
	t_segment	*seg;

	data->ambig_redir = 0;
	current = data->token;
	while (current != NULL)
	{
		seg = current->segments;
		while (seg)
		{
			expanded = expand_segment(data, seg, current);
			if (!expanded)
				return ;
			ft_free(&seg->text);
			seg->text = expanded;
			seg = seg->next;
			if (process_token_redirection(data, &current))
				return ;
		}
		current = current->next;
	}
}

char	*expand(t_data *data, char *word)
{
	t_expander	expander;

	if (!initialize_expander(&expander, word))
		return (NULL);
	while (word[expander.index_word] != '\0')
	{
		if (word[expander.index_word] == '$')
		{
			expander.index_word++;
			if (handle_special_dollar(data, word, &expander) == -1)
				return (NULL);
		}
		else
		{
			if (handle_regular_char(word[expander.index_word++],
					&expander) == -1)
				return (NULL);
		}
	}
	expander.result[expander.index_res] = '\0';
	return (expander.result);
}
