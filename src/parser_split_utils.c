/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 22:28:18 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/24 22:38:14 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *slice(char *word, size_t start, size_t length)
{
    if (length > 0)
        return (ft_substr(word, start, length));
    else
        return (NULL);
}

void    update_data_token(t_data *data, t_token *left, t_token *first_new)
{
    if (!left && first_new)
        data->token = first_new;
}

t_token *update_pointer(t_split *tokens)
{
    if (tokens->suffix)
        return tokens->suffix->right;
    else if (tokens->quoted)
        return tokens->quoted->right;
    else if (tokens->prefix)
        return tokens->prefix->right;
    else
        return (NULL);
}
