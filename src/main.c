/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/18 17:39:05 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char prompt[] = "minishell> ";

//DELETE THIS WHEN DONE
//getcmd is a function that reads a line from the terminal
//and stores it in the buffer
//it returns the number of characters read
/*void	parse_cmd(t_data *data)*/
/*{*/
/*	int i = 0;*/
/**/
/*	data->exec = ft_calloc(1, sizeof(t_exec));*/
/*	while (data->token)*/
/*	{*/
/*		if (i == 0)*/
/*			data->exec->cmd = ft_strdup(data->token->word);*/
/*		data->exec->av = ft_calloc(10 + 1, sizeof(char *));*/
/*		data->exec->av[i] = ft_strdup(data->token->word);*/
/*		data->exec->type = CMD;*/
/*		data->token = data->token->right;*/
/*		i++;*/
/*	}*/
/*}*/

int	skill_check(t_data *data)
{
	int i;
	int j;
	int dq_count;
	int sq_count;

	i = -1;
	dq_count = 0;
	sq_count = 0;
	while (data->line[++i])
	{
		if (data->line[i] == DQ)
		{
			j = i + 1;
			dq_count++;
			while (data->line[j] && data->line[j] != DQ)
				j++;
			if (data->line[j] == DQ)
				dq_count++;
			i = j;
		}
		else if (data->line[i] == SQ)
		{
			j = i + 1;
			while (data->line[j] && data->line[j] != SQ)
				j++;
			if (data->line[j] == SQ)
				sq_count++;
			i = j;
		}
	}
	if (dq_count % 2 != 0 || sq_count % 2 != 0)
	{
		ft_putstr_fd("Skill issue\n", 2);
		return (1);
	}
	return (0);
}

//Hello World
int main(int argc, char **argv, char **ev)
{
	t_data *data;
	(void)argc;
	(void)argv;

	data = ft_calloc(1, sizeof(t_data));
	parse_env(data, ev);
	while (1)
	{
		data->line = readline(prompt);
		if (skill_check(data))
			continue ;
		if (!data->line)
			bruh(data, "Failed to read line", 1);
		parse_line(data);
		tokenization(data);
		init_exec_data(data);
		/*parse_cmd(data);*/
		runcmd(data); //need exec function
	}
	bruh(data, NULL, 0);
}
