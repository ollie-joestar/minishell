/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:38:58 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/11 11:23:11 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char prompt[] = "minishell> ";

void	runcmd(t_data *data)
{
}

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

//
//WORST CASE
//minishell> < infile1 << "lim" > outfile1 echo hello world > outfile2 < infile2 | < infile3 "ca""t" > outfile3 *** BONUS PART***  && echo hello world
// ";" not implemented
//< infile > outfile NOT NEEDED !!!!!!!!!!
//< infile cat > outfile should work
//< infile cat | > outfile should NOT WORK

int main(int argc, char **argv, char **ev)
{
	static char buf[1024];
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	data->ev = ev;

	while (1)
	{
		ft_putstr_fd(prompt, 1);
		if (getcmd(buf, sizeof(buf)) >= 0)
		{
			runcmd(data);
		}
		else
			break;
	}
	bruh(data, NULL, 0);
}
