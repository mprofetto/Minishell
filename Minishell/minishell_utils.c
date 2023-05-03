/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:09:02 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 11:33:24 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_protected(t_shell *shell, char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		free_and_print_strerror(shell);
	return (result);
}

int	len_tab(char **tb)
{
	int	i;

	i = 0;
	if (!tb)
		return (0);
	while (tb[i])
		++i;
	return (i);
}

int	ft_lstsize_pipe(t_pipe_node *lst)
{
	int		result;

	if (!lst)
		return (0);
	result = 1;
	while (lst->next)
	{
		lst = lst->next;
		result++;
	}
	return (result);
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		perror(NULL);
}

void	shell_fd_control(t_shell *shell, char operation, int i)
{
	if (operation == '+')
		shell->fd_opened += i;
	else
		shell->fd_opened -= i;
	if (shell->fd_opened > FOPEN_MAX)
	{
		printf("minishell: Max opened fd limit reached\n");
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
}

void	close_fd(t_shell *shell, int fd)
{
	shell_fd_control(shell, '-', 1);
	close(fd);
}

char	*get_string_from_fd(t_shell *shell, int fd)
{
	char	*str;
	char	*temp;
	char	*result;

	str = get_next_line(fd, 100);
	result = NULL;
	while (str)
	{
		temp = ft_strjoin_protected(shell, result, str);
		free(str);
		if (result)
			free(result);
		result = temp;
		str = get_next_line(fd, 100);
	}
	return (result);
}

void	update_exit_status_with_errno(t_shell *shell)
{
	char	*result;
	char	*errno_value;

	errno_value = ft_itoa(errno);
	result = ft_strjoin_protected(shell, "?=", errno_value);
	free(errno_value);
	export(shell, result);
}
