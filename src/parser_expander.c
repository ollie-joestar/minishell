/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:46:04 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/04 21:00:24 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Expand a segment of a token and empty token check
char	*expand_segment(t_data *data, t_segment *seg, t_token *token)
{
	char	*expanded;

	(void)token;
	data->segment = seg;
	if (seg->single_quoted)
		return (ft_strdup(seg->text));
	expanded = expand(data, seg->text);
	if (!expanded)
		return (NULL);
	return (expanded);
}

// Process redirections and check for ambiguous redirections
int	process_token_redirection(t_data *data, t_token **token)
{
	if ((*token)->type != WORD && (*token)->type != PIPE)
	{
		process_redirection(data, token);
		if (data->ambig_redir)
			return (free_tokens(data), 1);
	}
	return (0);
}

//Cycle through all tokens and expand them
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

// Expansion begins here
char	*expand(t_data *data, char *word)
{
	t_exp	exp;

	if (!word || !data)
		return (NULL);
	if (!initialize_expander(&exp, word))
		return (NULL);
	while (word[exp.index_word] != '\0')
	{
		if (word[exp.index_word] == '$')
		{
			exp.index_word++;
			if (process_dollar_value(data, word, &exp))
				return (ft_free(&exp.result), NULL);
		}
		else
			handle_normal_chars(word[exp.index_word++], &exp);
	}
	return (exp.result);
}
