/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2025/02/24 17:54:37 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skill_check(t_data *data)
{
	int	i;

	i = -1;
	if (!data->line)
		bruh(data, "exit", data->status);
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

int	stop_right_there_criminal(t_data *data)
{
	if (g_signal == SIGINT && !lpid(data))
	{
		data->status = 130;
		g_signal = 0;
	}
	if (skill_check(data))
	{
		ft_free(&data->line);
		return (0);
	}
	if (!data->line || !*data->line)
		return (0);
	return (1);
}

int	parse_and_validate_line(t_data *data)
{
	parse_line(data);
	if (!valid_syntax(data, data->token))
		return (free_tokens(data), ft_free(&data->line), 0);
	return (1);
}

int	process_tokens_and_ambig_check(t_data *data)
{
	process_tokens(data);
	if (data->ambig_redir)
		return (ft_free(&data->line), 0);
	return (1);
}

int	main(int argc, char **argv, char **ev)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		bruh(data, "Failed to allocate memory", 1);
	data->env = parse_env(data, ev);
	setup_signal_mode(data, 1);
	while (1)
	{
		data->line = readline("minishell > ");
		if (!stop_right_there_criminal(data))
			continue ;
		if (!parse_and_validate_line(data))
			continue ;
		if (!process_tokens_and_ambig_check(data))
			continue ;
		init_exec(data);
		setup_signal_mode(data, 0);
		run(data);
		setup_signal_mode(data, 1);
	}
	bruh(data, NULL, 0);
}
