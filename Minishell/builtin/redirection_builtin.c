/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:50:00 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/21 11:08:34 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_pipe_node *pipe)
{
	if (ft_strcmp(pipe->arguments[0], "cd") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "echo") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "env") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "exit") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "export") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "unset") == 0)
		return (1);
	return (0);
}

int	redirection_builtin2(t_shell *shell, t_pipe_node *pipe)
{
	if (ft_strcmp(pipe->arguments[0], "export") == 0)
	{
		builtin_export(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "pwd") == 0)
	{
		builtin_pwd(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "unset") == 0)
	{
		builtin_unset(shell, pipe);
		return (1);
	}
	return (0);
}

int	redirection_builtin(t_shell *shell, t_pipe_node *pipe)
{
	if (ft_strcmp(pipe->arguments[0], "cd") == 0)
	{
		builtin_cd(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "echo") == 0)
	{
		builtin_echo(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "env") == 0)
	{
		builtin_env(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "exit") == 0)
	{
		builtin_exit(shell, pipe);
		return (1);
	}
	return(redirection_builtin2(shell, pipe));
}
