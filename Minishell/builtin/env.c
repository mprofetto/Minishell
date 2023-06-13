/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:15:31 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/11 15:57:22 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function can be launched in multiples pipe in forks or as a single 
pipe in a fork*/

int	builtin_env(t_shell *shell, t_pipe_node *node, int fd_out)
{
	int	redir_check;

	redir_check = open_close_inputs(shell, node->input_file_lst);
	if (redir_check != 0)
		return (redir_check);
	redir_check = write_array_to_outputs(shell->envp, node->output_file_lst);
	if (redir_check != 0)
		return (redir_check);
	else
		ft_print_str_array_fd(shell->envp, fd_out);
	return (0);
}