/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:17:06 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/14 11:49:30 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_len(t_envlist *env)
{
	size_t	len;

	len = 0;
	if (!env)
		return (0);
	while (env->prev)
		env = env->prev;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}
