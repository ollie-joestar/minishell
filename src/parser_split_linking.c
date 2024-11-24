/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_token_linking.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 22:30:25 by hanjkim           #+#    #+#             */
/*   Updated: 2024/11/24 22:35:34 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    adjust_links(t_token *token, t_token *left, t_token *right)
{
    if (token) {
        token->left = left;
        token->right = right;
        if (left)
            left->right = token;
        if (right)
            right->left = token;
    }
}

void    adjust_prefix_links(t_token *prefix, t_token *left,
                            t_token *right, t_split *tokens) {
    t_token *next;
    
    next = NULL;
    if (tokens->quoted)
        next = tokens->quoted;
    else if (tokens->suffix)
        next = tokens->suffix;
    else
        next = right;
    adjust_links(prefix, left, next);
}

void    adjust_quoted_links(t_token *quoted, t_token *left, 
                            t_token *right, t_split *tokens) {
    t_token *prev;
    t_token *next;

    prev = NULL;
    next = NULL;
    if (tokens->prefix)
        prev = tokens->prefix;
    else
        prev = left;
    if (tokens->suffix)
        next = tokens->suffix;
    else
        next = right;
    adjust_links(quoted, prev, next);
}

void    adjust_suffix_links(t_token *suffix, t_token *left, 
                         t_token *right, t_split *tokens) 
{
    t_token *prev;

    prev = NULL;
    if (tokens->quoted)
        prev = tokens->quoted;
    else if (tokens->prefix)
        prev = tokens->prefix;
    else
        prev = left;
    adjust_links(suffix, prev, right);
}
