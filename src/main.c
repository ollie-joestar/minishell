/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 17:31:44 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
char prompt[] = "minishell> ";

//DELETE THIS WHEN DONE
//getcmd is a function that reads a line from the terminal
//and stores it in the buffer
//it returns the number of characters read
void	parse_cmd(t_data *data)
{
	int i = 0;

	data->exec = ft_calloc(1, sizeof(t_exec));
	while (data->token)
	{
		if (i == 0)
			data->exec->cmd = ft_strdup(data->token->word);
		data->exec->av = ft_calloc(10 + 1, sizeof(char *));
		data->exec->av[i] = ft_strdup(data->token->word);
		data->exec->type = CMD;
		data->token = data->token->right;
		i++;
	}
}


// UNSAFE FUNCTION FIX LATER
void	store_env(t_data *data, char **ev)
{
	int i;
	int j;

	i = 0;
	while (ev[i])
		i++;
	data->ev = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (ev[i])
	{
		data->ev[i] = ft_strdup(ev[i]);
		i++;
	}
}

int main(int argc, char **argv, char **ev)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	store_env(data, ev);
	while (1)
	{
		data->line = readline(prompt);
		if (!data->line)
			bruh(data, "Failed to read line", 1);
		tokenization(data);
		parse_cmd(data);
		runcmd(data); //need exec function
	}
	bruh(data, NULL, 0);
}
