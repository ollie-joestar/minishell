/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/19 15:08:12 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	i;

	i = -1;
	if (!data->line)
		return (ft_putstr_fd("No line\n", 2), 1);
	while (data->line[++i])
	{
		if (data->line[i] == DQ)
		{
			i++;
			while (data->line[i] && data->line[i] != DQ)
				i++;
			if (data->line[i] != DQ)
				return (ft_putstr_fd("Skill issue\n", 2), 1);
		}
		else if (data->line[i] == SQ)
		{
			i++;
			while (data->line[i] && data->line[i] != SQ)
				i++;
			if (data->line[i] != SQ)
				return (ft_putstr_fd("Skill issue\n", 2), 1);
		}
	}
	return (0);
}

/*int	skill_check(t_data *data)*/
/*{*/
/*	int i;*/
/*	int j;*/
/*	int dq_count;*/
/*	int sq_count;*/
/**/
/*	i = -1;*/
/*	dq_count = 0;*/
/*	sq_count = 0;*/
/*	while (data->line[++i])*/
/*	{*/
/*		if (data->line[i] == DQ)*/
/*		{*/
/*			j = i + 1;*/
/*			dq_count++;*/
/*			while (data->line[j] && data->line[j] != DQ)*/
/*				j++;*/
/*			if (data->line[j] == DQ)*/
/*				dq_count++;*/
/*			i = j;*/
/*		}*/
/*		else if (data->line[i] == SQ)*/
/*		{*/
/*			j = i + 1;*/
/*			while (data->line[j] && data->line[j] != SQ)*/
/*				j++;*/
/*			if (data->line[j] == SQ)*/
/*				sq_count++;*/
/*			i = j;*/
/*		}*/
/*	}*/
/*	if (dq_count % 2 != 0 || sq_count % 2 != 0)*/
/*		return (ft_putstr_fd("Skill issue\n", 2), 1);*/
/*	return (0);*/
/*}*/

#include <stdio.h>
//Hello World
int main(int argc, char **argv, char **ev)
{
	t_data *data;
	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		bruh(data, "Failed to allocate memory", 1);
	parse_env(data, ev);
	setup_signal_mode(data, 1); //Try Ctrl + \, Ctrl + C. If it doesn't work, just comment it out
	while (1)
	{
		ft_printf("Readline\n");
		data->line = readline("minishell > ");
		/*if (g_signal == SIGINT)*/
		/*          		g_signal = 0, continue;*/
		ft_printf("Skill check\n");
		if (skill_check(data))
		{
			ft_free(&data->line);
			continue;
		}
		if (!data->line || !*data->line)
			bruh(data, "Failed to read line", 1);
		parse_line(data);
		tokenization(data);
		/*ft_printf("after tokenization\n");*/
		ft_printf("Initiating exec data\n");
		init_exec_data(data);
		/*ft_printf("after init_exec_data\n");*/
		/*parse_cmd(data);*/
		ft_printf("Executing\n");
		runcmd(data); //need exec function
	}
	bruh(data, NULL, 0);
}
