/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/12 16:24:48 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
char prompt[] = "minishell> ";

//DELETE THIS WHEN DONE
t_exec	*parsecmd(t_data *data, char *s)
{
	t_exec *exec;

	return (exec);
}

//DELETE THIS WHEN DONE
//getcmd is a function that reads a line from the terminal
//and stores it in the buffer
//it returns the number of characters read
int	getcmd(char *buf, int nbuf)
{
	if (fgets(buf, nbuf, stdin) == NULL)
		return -1;
	if (buf[0] == 0)
		return -1;
	return 0;
}

bool	parse_tokens(t_data *data)
{
	if (data->token == NULL)
		return (false);
	return (true);
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
		if (parse_tokens(data) == true)
			runcmd(data); //need exec function
		else
			break;
	}
	bruh(data, NULL, 0);
}
