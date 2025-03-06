/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <oohnivch@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:39:59 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/06 15:00:04 by hanjkim          ###   ########.fr       */
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
				return (ft_putstr_fd("skill issue.\n", 2), 1);
		}
		else if (data->line[i] == SQ)
		{
			i++;
			while (data->line[i] && data->line[i] != SQ)
				i++;
			if (data->line[i] != SQ)
				return (ft_putstr_fd("skill issue.\n", 2), 1);
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
		return (ft_free(&data->line), 0);
	if (!data->line || !*data->line)
		return (ft_free(&data->line), 0);
	return (1);
}

int	parse_and_validate_line(t_data *data)
{
	parse_line(data);
	if (!valid_syntax(data, data->token))
	{
		add_history(data->line);
		return (free_tokens(data), ft_free(&data->line), 0);
	}
	return (1);
}

int	process_tokens_and_ambig_check(t_data *data)
{
	process_tokens(data);
	if (data->status == 130)
	{
		add_history(data->line);
		return (free_tokens(data), ft_free(&data->line), 0);
	}
	if (data->ambig_redir)
		return (add_history(data->line), ft_free(&data->line), 0);
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
		/*data->line = readline("minishell > ");*/
		data->line = ft_strdup("ccd notexists");
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
		break ;
	}
	bruh(data, NULL, data->status);
}
