/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:38:56 by oohnivch          #+#    #+#             */
/*   Updated: 2024/11/07 11:53:10 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_cmd	*init_execcmd(void)
{
	struct s_execcmd *cmd;

	cmd = ft_calloc(sizeof(struct s_cmd), 1);
	cmd->type = EXEC;
	return ((struct s_cmd*)cmd);
}

struct s_cmd	*init_redircmd(struct s_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	struct s_redircmd *cmd;

	cmd = ft_calloc(sizeof(struct s_cmd), 1);
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((struct s_cmd*)cmd);
}

struct s_cmd	*init_pipecmd(struct s_cmd *left, struct s_cmd *right)
{
	struct s_pipecmd *cmd;

	cmd = ft_calloc(sizeof(struct s_cmd), 1);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((struct s_cmd*)cmd);
}

struct s_cmd	*init_listcmd(struct s_cmd *left, struct s_cmd *right)
{
	struct s_listcmd *cmd;

	cmd = ft_calloc(sizeof(struct s_cmd), 1);
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;
	return ((struct s_cmd*)cmd);
}

struct s_cmd	*init_backcmd(struct s_cmd *subcmd)
{
	struct s_cmd *cmd;

	cmd = ft_calloc(sizeof(struct s_cmd), 1);
	cmd->type = BACK;
	return (cmd);
}
