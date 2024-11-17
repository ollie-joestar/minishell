/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:41:49 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/17 16:42:40 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex_token	*create_token(void)
{
	t_lex_token	*token;

	token = (t_lex_token *)ft_calloc(1, (sizeof(t_lex_token)));
	if (!token)
		return (NULL);
	return (token);
}

void	init_tokens(t_data *data)
{
	int		i;
	char	**av;
	t_lex_token	*temp;

	av = ft_split(data->line, ' ');
	if (!av)
		bruh(data, "Failed to split line", 1);
	i = -1;
	while (av[++i])
	{
		temp = create_token();
		if (!temp)
			bruh(data, "Failed to create token", 1);
		temp->word = av[i];
		if (!data->token)
			data->token = temp;
		if(data->token)
		{
			data->token->right = temp;
			temp->left = data->token;
			data->token = temp;
		}
	}
}
