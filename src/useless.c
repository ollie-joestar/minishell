/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:45:11 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/18 16:17:32 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
