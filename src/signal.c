
#include "minishell.h"

sig_atomic_t	g_signal = 0;

void	handle_sigint(int sig)
{
	g_signal = sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	save_sigint(int signal)
{
	g_signal = signal;
}

void	sigint_handler_non_interactive_mode(t_data *data)
{
	data->sa.sa_handler = save_sigint;
	sigaction(SIGINT, &data->sa, NULL);
}

void	sigint_handler_interactive_mode(t_data *data)
{
	data->sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &data->sa, NULL);
}

void	setup_signal_handlers(t_data *data)
{
	signal(SIGQUIT, SIG_IGN);
	data->sa.sa_flags = SA_RESTART;
	sigemptyset(&data->sa.sa_mask);
	sigint_handler_interactive_mode(data);
}
