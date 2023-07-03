/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpids.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/03 13:58:32 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_waitpids(t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < shell->nbr_cmds)
	{
		waitpid(shell->pids[i], &status, 0);
		++i;
	}
	if (status == SIGINT || shell->last_exit_status == 130)
		shell->last_exit_status = EOWNER_DEAD;
	else if (status == SIGQUIT)
	{
		printf("Quit: 3\n");
		shell->last_exit_status = INTERRUPTED_BY_SIGNAL;
	}
	else
	{
			shell->last_exit_status = status / 256;
	}
	shell->nbr_cmds = lstsize_cmd(shell->pipe_lst);
}
