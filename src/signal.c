/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:13:23 by hanjkim           #+#    #+#             */
/*   Updated: 2024/12/18 21:32:32 by hanjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handle_sigint(int sig)
{
	g_signal = sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	catch_sigint(int sigint)
{
	g_signal = sigint;
}

void	setup_signal_handler(t_data *data, void (*handler)(int))
{
	data->sa.sa_handler = handler;
	data->sa.sa_flags = SA_RESTART;
	sigemptyset(&data->sa.sa_mask);
	sigaction(SIGINT, &data->sa, NULL);
}

void	setup_signal_mode(t_data *data, int interactive)
{
	signal(SIGQUIT, SIG_IGN);
	if (interactive)
		setup_signal_handler(data, handle_sigint);
	else
		setup_signal_handler(data, catch_sigint);
}

void	check_exit_status(t_data *data, int exit_status)
{
	if (WIFEXITED(exit_status))
		data->status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		data->status = WTERMSIG(exit_status) + 128;
}
