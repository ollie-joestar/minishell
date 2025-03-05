/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <hanjkim@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:26:35 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/05 15:48:12 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Get the filename token for the redirection token
t_token	*get_filename_token(t_data *data, t_token *redir_token)
{
	t_token	*filename_token;

	filename_token = redir_token->next;
	if (!filename_token)
	{
		unexpected_token(data, NULL);
		return (NULL);
	}
	filename_token->type = WORD;
	if (redir_token->type == HEREDOC)
	{
		filename_token = handle_heredoc(data, redir_token, filename_token);
		if (!filename_token)
			return (NULL);
	}
	else if (redir_token->type == INPUT || redir_token->type == REPLACE
		|| redir_token->type == APPEND)
		filename_token->type = redir_token->type;
	return (filename_token);
}

// Check if the filename token has split words
int	check_split_words(t_data *data, t_token *filename_token,
						char **final_filename)
{
	char		**split_words;
	char		*orig_filename;
	int			count;
	int			i;

	orig_filename = join_segments(filename_token);
	if (!orig_filename)
		orig_filename = ft_strdup("");
	split_words = ft_split_set(*final_filename, " \t\n\r\v\f");
	if (!split_words)
		return (ft_free(&orig_filename), 1);
	count = 0;
	i = -1;
	if (split_words)
		while (split_words[++i])
			count++;
	if (split_words && has_unquoted_segment(filename_token) && count > 1)
	{
		data->status = 1;
		data->ambig_redir = 1;
		mspec2(orig_filename, "ambiguous redirect\n");
		ft_free(&orig_filename);
		return (ft_free(final_filename), free_arr(&split_words), 1);
	}
	return (free_arr(&split_words), ft_free(&orig_filename), 0);
}

// Check if the redirection is ambiguous (ie invalid filename)
int	check_ambiguous_redirect(t_data *data, t_token *filename_token,
								char **final_filename)
{
	char	*orig_filename;

	*final_filename = finalize_redirection_token(data, filename_token);
	if (check_split_words(data, filename_token, final_filename))
		return (ft_free(final_filename), 1);
	if (!*final_filename || (*final_filename)[0] == '\0')
	{
		orig_filename = join_segments(filename_token);
		if (!orig_filename)
			orig_filename = ft_strdup("");
		if ((*final_filename)[0] == '\0' && data->segment->env_not_found)
			mspec2(orig_filename, "ambiguous redirect\n");
		else if ((*final_filename)[0] == '\0')
			mspec2(orig_filename, "No such file or directory\n");
		data->status = 1;
		data->ambig_redir = 1;
		(ft_free(&orig_filename), ft_free(final_filename));
		return (1);
	}
	return (0);
}

// Link the filename token to the redirection token
void	link_filename_token(t_data *data, t_token *redir_token,
							t_token *filename_token, char *final_filename)
{
	free_token_segments(filename_token);
	filename_token->word = final_filename;
	filename_token->prev = redir_token->prev;
	if (filename_token->next)
		filename_token->next->prev = filename_token;
	if (filename_token->prev)
		filename_token->prev->next = filename_token;
	else
		data->token = filename_token;
	free_old_token(redir_token);
}

// Process redirection token
void	process_redirection(t_data *data, t_token **token)
{
	t_token	*redir_token;
	t_token	*filename_token;
	char	*final_filename;

	redir_token = *token;
	filename_token = get_filename_token(data, redir_token);
	if (!filename_token)
		return ;
	if (check_ambiguous_redirect(data, filename_token, &final_filename))
		return ;
	link_filename_token(data, redir_token, filename_token, final_filename);
	*token = filename_token;
}
