/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:46:04 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/08 20:43:51 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
