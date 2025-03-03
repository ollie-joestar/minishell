/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjkim <@student.42vienna.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:13:23 by hanjkim           #+#    #+#             */
/*   Updated: 2025/03/03 12:48:28 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// global variable to check for signal (parent & here_doc)
volatile sig_atomic_t	g_signal = 0;

// injects newline when SIGINT is caught (needed for readline)
void	handle_sigint(int sig)
{
	g_signal = sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

// catches SIGINT and sets g_signal to sigint (Ctrl+C)
void	catch_sigint(int sigint)
{
	g_signal = sigint;
}

// sets up signal mode for interactive and non-interactive mode
// interactive mode: SIGINT is handled by handle_sigint
// non-interactive mode: SIGINT is handled by catch_sigint
// SIGQUIT is ignored in both modes
void	setup_signal_mode(t_data *data, int interactive)
{
	if (interactive)
	{
		data->sa_int.sa_handler = handle_sigint;
		data->sa_int.sa_flags = SA_RESTART;
		sigemptyset(&data->sa_int.sa_mask);
		sigaction(SIGINT, &data->sa_int, NULL);
		data->sa_quit.sa_handler = SIG_IGN;
		data->sa_quit.sa_flags = SA_RESTART;
		sigemptyset(&data->sa_quit.sa_mask);
		sigaction(SIGQUIT, &data->sa_quit, NULL);
	}
	else
	{
		data->sa_int.sa_handler = catch_sigint;
		data->sa_int.sa_flags = SA_RESTART;
		sigemptyset(&data->sa_int.sa_mask);
		sigaction(SIGINT, &data->sa_int, NULL);
	}
}

// checks exit status and sets data->status accordingly
// In case of Ctrl+\, prints "(Quit) Core dumped" and sets status to 131
void	check_exit_status(t_data *data, int exit_status)
{
	int	sig;

	if (WIFEXITED(exit_status))
		data->status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
	{
		sig = WTERMSIG(exit_status);
		if (sig == SIGQUIT)
		{
			ft_putendl_fd("(Quit) Core dumped", STDERR_FILENO);
			data->status = 131;
		}
		else
			data->status = sig + 128;
	}
}
