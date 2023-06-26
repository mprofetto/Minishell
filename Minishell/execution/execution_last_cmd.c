/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_last_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/23 16:23:23 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	last_cmd2(t_shell *shell, t_pipe_node *pipe)
{
	(void)shell;
	if (pipe->iofiles[0] == 1)
	{
		ft_close(pipe->fdio[0]);
		dup2(pipe->fdio[0], STDIN_FILENO);
		if (pipe->fdio[0] != -1)
			ft_close(pipe->fdio[0]);
	}
	else
		dup2(pipe->fd[0], STDIN_FILENO);
	if (pipe->iofiles[1] == 1)
	{
		dup2(pipe->fdio[1], STDOUT_FILENO);
		ft_close_files(pipe->fdio[1], "fdio[1] first cmd output");
	}
	else
		dup2(1, STDOUT_FILENO);
}

void	last_cmd(t_shell *shell, t_pipe_node *pipe, int i)
{
	find_path(shell, pipe);
	shell->pids[i] = ft_fork(shell);
	if (shell->pids[i] == 0)
	{
		if (!pipe->arguments[0])
			exit(EXIT_FAILURE);
		last_cmd2(shell, pipe);
		ft_close_files(pipe->fd[0], "fd[0] last cmd");
		if (redirection_builtin(shell, pipe) == 0)
			execve(pipe->path, pipe->arguments, shell->envp);
		exit(EXIT_FAILURE);
	}
}
