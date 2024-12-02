/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/12/02 20:29:49 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skill_check(t_data *data)
{
	int	i;

	i = -1;
	if (!data->line)
		bruh(data, "exit", 0);
	while (data->line[++i])
	{
		if (data->line[i] == DQ)
		{
			i++;
			while (data->line[i] && data->line[i] != DQ)
				i++;
			if (data->line[i] != DQ)
				return (ft_putstr_fd("skill issue\n", 2), 1);
		}
		else if (data->line[i] == SQ)
		{
			i++;
			while (data->line[i] && data->line[i] != SQ)
				i++;
			if (data->line[i] != SQ)
				return (ft_putstr_fd("skill issue\n", 2), 1);
		}
	}
	return (0);
}

int main(int argc, char **argv, char **ev)
{
	t_data *data;
	(void)argc;
	(void)argv;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		bruh(data, "Failed to allocate memory", 1);
	data->env = parse_env(data, ev);
	/*if (!data->env)*/
	/*	bruh(data, "Failed to parse env", 1);*/
	setup_signal_mode(data, 1);
	while (1)
	{
		data->line = readline("minishell > "); //funcheck failed
		if (g_signal == SIGINT && data->pid != 0)
			g_signal = 0;
		if (skill_check(data))
		{
			ft_free(&data->line);
			continue;
		}
		if (!data->line || !*data->line)
			continue;
		/*ft_printf("Parsing line->\n");*/
		parse_line(data);
		/*print_tokens(data->token);*/
		/*ft_printf("Tokenization->\n");*/
		process_tokens(data);
		/*print_tokens(data->token);*/
		/*ft_printf("Initiating exec data->\n");*/
		init_exec_data(data);
		/*ft_printf("after init_exec_data\n");*/
		/*ft_printf("\nPrinting exec data->");*/
		/*print_exec(data->exec);*/
		/*ft_printf("\nExecuting->\n");*/
		run(data);
	}
	bruh(data, NULL, 0);
}
