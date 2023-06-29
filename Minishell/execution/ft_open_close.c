/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:00:10 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/28 09:47:20 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	next_file(t_redir_datas	*temp_lst, int fd, char *value)
{
	while (temp_lst)
	{
		temp_lst = temp_lst->next;
		if (temp_lst)
		{
			if (temp_lst->type == 'i')
			{
				ft_close(fd, value);
				temp_lst = temp_lst->last;
			}
		}
	}
}

int	ft_open_infile(t_shell *shell, t_redir_datas *input_lst)
{
	int				fd;
	t_redir_datas	*temp_lst;

	temp_lst = input_lst;
	if (input_lst->mode == 1)
		fd = open(input_lst->value, O_RDONLY);
	else
	{
		printf("heredoc -> to do\n");
		exit(0);
	}
	if (fd == -1)
	{
		perror(input_lst->value);
		ft_exit_cmd(shell, 127);
	}
	next_file(temp_lst, fd, input_lst->value);
	return (fd);
}

int	ft_open_outfile(t_shell *shell, t_redir_datas *output_lst)
{
	int				fd;
	t_redir_datas	*temp_lst;

	temp_lst = output_lst;
	if (output_lst->mode == 1)
		fd = open(output_lst->value,
				O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	else
	{
		fd = open(output_lst->value,
				O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	}
	if (fd == -1)
	{
		perror(output_lst->value);
		ft_exit_cmd(shell, 127);
	}
	next_file(temp_lst, fd, output_lst->value);
	return (fd);
}

void	openiofile(t_shell *shell, t_pipe_node *pipe, t_redir_datas *files)
{
	if (files->type == 'i' && shell->exit == 1)
	{
		if (files->mode == 2)
			pipe->fdio[0] = get_heredoc(shell, files->value);
		else
			pipe->fdio[0] = ft_open_infile(shell, files);
		pipe->iofiles[0] = 1;
	}
	if (files->type == 'o' && shell->exit == 1)
	{
		pipe->fdio[1] = ft_open_outfile(shell, files);
		pipe->iofiles[1] = 1;
	}
	if (files->next && shell->exit == 1)
		openiofile(shell, pipe, files->next);
}