/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:49:14 by hanjkim           #+#    #+#             */
/*   Updated: 2025/01/26 21:18:19 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finalize_tokens(t_token *token_list)
{
	t_token		*curr;
	t_segment	*seg;
	t_segment	*next;
	char		*joined;

	curr = token_list;
	while (curr)
	{
		if (curr->segments)
		{
			joined = join_segments(curr);
			seg = curr->segments;
			while (seg)
			{
				next = seg->next;
				ft_free(&seg->text);
				free(seg);
				seg = next;
			}
			curr->segments = NULL;
			curr->word = joined;
		}
		curr = curr->next;
	}
}

void	process_redirection(t_data *data, t_token **token)
{
	t_token	*redirection_token;
	t_token	*filename_token;

	redirection_token = *token;
	filename_token = redirection_token->next;
	if (!filename_token)
	{
		unexpected_token(data, NULL);
		return ;
	}
	filename_token->type = WORD;
	if (redirection_token->type == HEREDOC)
	{
		filename_token = handle_heredoc(data, redirection_token,
				filename_token);
		if (!filename_token)
			return ;
	}
	else if (redirection_token->type == INPUT
		|| redirection_token->type == REPLACE
		|| redirection_token->type == APPEND)
		filename_token->type = redirection_token->type;
	filename_token->prev = redirection_token->prev;
	if (filename_token->next)
		filename_token->next->prev = filename_token;
	if (filename_token->prev)
		filename_token->prev->next = filename_token;
	else
		data->token = filename_token;
	free_old_token(redirection_token);
	*token = filename_token;
	/*ft_printf("filename_token->word: %s\n", filename_token->word);*/
}

char	*join_fields_with_single_space(char **fields)
{
	size_t	total_len;
	int		i;
	char	*joined;
	int		j;

	total_len = 0;
	i = -1;
	while (fields[++i])
		total_len += ft_strlen(fields[i]);
	if (i > 1)
		total_len += (i - 1);
	joined = ft_calloc(total_len + 1, 1);
	if (!joined)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		if (j > 0)
		{
			if (ft_strlcat(joined, " ", total_len + 1) >= total_len + 1)
				return (ft_free(&joined), NULL);
		}
		if (ft_strlcat(joined, fields[j], total_len + 1) >= total_len + 1)
			return (ft_free(&joined), NULL);
	}
	return (joined);
}

/*char	*expand_redirection_segment(t_data *data, t_segment *seg, t_token *token)*/
/*{*/
/*	char	*expanded;*/
/**/
/*	(void)token;*/
/*	if (seg->single_quoted)*/
/*		return (ft_strdup(seg->text));*/
/*	expanded = expand(data, seg->text);*/
/*	if (!expanded)*/
/*	{*/
/*		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);*/
/*		data->status = 1;*/
/*		return (NULL);*/
/*	}*/
/*	if (expanded[0] == '\0')*/
/*	{*/
/*		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);*/
/*		free(expanded);*/
/*		data->status = 1;*/
/*		return (NULL);*/
/*	}*/
/**/
/*	return (expanded);*/
/*}*/

char	*expand_segment(t_data *data, t_segment *seg, t_token *token)
{
	char	*expanded;
	char	**fields;
	char	*joined;

	/*if (token->type != WORD && token->type != PIPE)*/
	/*	return (expand_redirection_segment(data, seg, token));*/
	(void)token;
	if (seg->single_quoted)
		return (ft_strdup(seg->text));
	expanded = expand(data, seg->text);
	if (!expanded)
		return (ft_strdup(""));
	if (!seg->double_quoted && !seg->single_quoted)
	{
		fields = ft_split(expanded, ' ');
		ft_free(&expanded);
		if (!fields)
			return (ft_strdup(""));
		joined = join_fields_with_single_space(fields);
		free_arr(&fields);
		if (!joined)
			return (ft_strdup(""));
		return (joined);
	}
	return (expanded);
}

void	expand_tokens(t_data *data)
{
	t_token		*current;
	char		*expanded;
	t_segment	*seg;

	current = data->token;
	while (current != NULL)
	{
		seg = current->segments;
		while (seg)
		{
			expanded = expand_segment(data, seg, current);
			if (!expanded)
				return ;
			else
			{
				ft_free(&seg->text);
				seg->text = expanded;
			}
			seg = seg->next;
			if (current->type != WORD && current->type != PIPE)
				process_redirection(data, &current);
		}
		current = current->next;
	}
}

/*void	expand_tokens(t_data *data)*/
/*{*/
/*	t_token *current;*/
/*	char *expanded;*/
/*	t_segment *seg;*/
/**/
/*	current = data->token;*/
/*	while (current != NULL)*/
/*	{*/
/*		seg = current->segments;*/
/*		while (seg)*/
/*		{*/
/*			if (current->type != WORD && current->type != PIPE)*/
/*				expanded = expand_redirection_segment(data, seg, current);*/
/*			else*/
/*				expanded = expand_segment(data, seg, current);*/
/*			if (!expanded)*/
/*				return ;*/
/*			ft_free(&seg->text);*/
/*			seg->text = expanded;*/
/*			seg = seg->next;*/
/*		}*/
/*		current = current->next;*/
/*	}*/
/*}*/
/**/
/*void process_all_redirections(t_data *data)*/
/*{*/
/*	t_token *current;*/
/**/
/*	current = data->token;*/
/*	while (current)*/
/*	{*/
/*		if (current->type != WORD && current->type != PIPE)*/
/*			process_redirection(data, &current);*/
/*		current = current->next;*/
/*	}*/
/*}*/

void	process_tokens(t_data *data)
{
	if (!data->token)
		bruh(data, "No tokens available for processing", 2);
	while (data->token && data->token->prev != NULL)
		data->token = data->token->prev;
	expand_tokens(data);
	while (data->token && data->token->prev != NULL)
		data->token = data->token->prev;
	/*process_all_redirections(data);*/
	/*while (data->token && data->token->prev != NULL)*/
	/*	data->token = data->token->prev;*/
	finalize_tokens(data->token);
}
