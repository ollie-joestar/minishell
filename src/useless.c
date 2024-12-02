/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:45:11 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/01 22:49:35 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*Posibly won't need this file anymore?*/
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
		tmp = tmp->next;
	}
}
