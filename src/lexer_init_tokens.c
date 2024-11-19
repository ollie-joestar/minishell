/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:41:49 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/19 19:57:13 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(void)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, (sizeof(t_token)));
	if (!token)
		return (NULL);
	return (token);
}

t_token	*init_tokens(t_data *data, char **av)
{
	int		i;
	t_token	*new_token;
	t_token	*temp;

	i = -1;
	new_token = NULL;
	while (av[++i])
	{
		temp = create_token();
		if (!temp)
			bruh(data, "Failed to create token", 1);
		temp->word = ft_strdup(av[i]);
		if (new_token)
		{
			new_token->right = temp;
			temp->left = new_token;
		}
		new_token = temp;
	}
	return (new_token);
}

void	parse_line(t_data *data)
{
	char	**av;
	
	if (!data->line)
		bruh(data, "No Input. bruh.", 1);
	av = ft_split(data->line, ' ');
	if (!av)
		bruh(data, "Failed to split line", 1);
	data->token = init_tokens(data, av);
	if (!data->token)
		bruh(data, "Failed to create tokens", 1);
	free_arr(&av);
}
