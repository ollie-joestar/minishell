/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reroute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:03:32 by oohnivch          #+#    #+#             */
/*   Updated: 2025/01/23 15:04:52 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*get_first_input(t_input *input)
{
	if (!input)
		return (NULL);
	while (input->prev)
		input = input->prev;
	return (input);
}

t_output	*get_first_output(t_output *output)
{
	if (!output)
		return (NULL);
	while (output->prev)
		output = output->prev;
	return (output);
}
