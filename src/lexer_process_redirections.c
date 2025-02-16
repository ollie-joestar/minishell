/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:26:35 by hanjkim           #+#    #+#             */
/*   Updated: 2025/02/16 16:38:08 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_ambiguous_redirect(t_data *data, t_token *filename_token,
										char **final_filename)
{
	char	*orig_filename;

	*final_filename = finalize_redirection_token(data, filename_token);
	if (!*final_filename || (*final_filename)[0] == '\0')
	{
		orig_filename = join_segments(filename_token);
		mspec2(orig_filename, "ambiguous redirect\n");
		ft_free(&orig_filename);
		data->status = 1;
		data->ambig_redir = 1;
		ft_free(final_filename);
		return (1);
	}
	return (0);
}

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
