/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:45:11 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/18 17:36:00 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	var_len(char *name)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(name[len]) || name[len] == '_')
		len++;
	return (len);
}

void	expand_vars_in_token(t_data *data, t_token *token, int i)
{
	char	*tmp;
	char	*value;
	char	*res;

	while (token->word[++i])
	{
		if (token->word[i] == '$')
		{
			tmp = ft_substr(token->word + i, 1, var_len(token->word + i + 1));
			value = expand(data, tmp);
			ft_free(&tmp);
			tmp = ft_substr(token->word, 0, i);
			res = ft_strjoin(tmp, value);
			ft_free(&tmp);
			tmp = ft_substr(token->word + i, var_len(token->word + i + 1) + 1,
				   ft_strlen(token->word));
			(ft_free(&token->word), ft_free(&value));
			i += var_len(token->word + i);
			token->word = ft_strjoin(res, tmp);
			(ft_free(&res), ft_free(&tmp));
		}
	}
}

void	expand_vars_in_token_list(t_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		expand_vars_in_token(data, tmp, -1);
		tmp = tmp->right;
	}
}

void	expand_dquote(t_data *data, t_token *token, char *word)
{
	t_token	*new;
	t_token *last_token_added;
	char	*tmp;
	char	*res;
	char	**av;

	last_token_added = token;
	res = word;
	if (!ft_strchr(res, DQ))
	{
		if (!last_token_added->right)
			return ;
		last_token_added = last_token_added->right;
		tmp = res;
		res = ft_strjoin(word, last_token_added->word);
		ft_free(&tmp);
	}
	av = ft_split(res, ' ');
	ft_free(&res);
	new = init_tokens(data, av);
	free_arr(av);
	insert_token(get_first_token(new), get_last_token(new), token);
	free_token_slice(token, last_token_added);
}

// word = ft_strchr(word, '\'' + 1);
void	expand_squote(t_data *data, t_token *token, char *word)
{
	t_token	*new;
	t_token *last_token_added;
	char	*tmp;
	char	*res;
	char	**av;

	last_token_added = token;
	res = word;
	if (!ft_strchr(res, SQ))
	{
		if (!last_token_added->right)
			return ;
		last_token_added = last_token_added->right;
		tmp = res;
		res = ft_strjoin(word, last_token_added->word);
		ft_free(&tmp);
	}
	av = ft_split(res, ' ');
	ft_free(&res);
	new = init_tokens(data, av);
	free_arr(av);
	insert_token(get_first_token(new), get_last_token(new), token);
	free_token_slice(token, last_token_added);
}
