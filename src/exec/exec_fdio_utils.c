/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fdio_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:55:08 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/15 22:55:14 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_init_fdio(t_exec *exec)
{
	if (exe_handle_files(exec))
		return (1);
	return (0);
}

int	exe_handle_files(t_exec *exec)
{
	t_filenames	*tmp;

	tmp = exec->redirs;
	while (tmp)
	{
		exe_redir_files(exec, tmp);
		if (exec->fd_in == -1 || exec-> fd_out == -1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	exe_redir_files(t_exec *exec, t_filenames *file)
{
	if (file->type == INFILE || file->type == N_HEREDOC)
	{
		if (exec->fd_in != STDIN_FILENO)
			close (exec->fd_in);
		exec->fd_in = open(file->path, O_RDONLY);
		if (exec->fd_in == -1)
			exe_err1_open(errno, file->path);
		exe_dup2_close(exec->fd_in, STDIN_FILENO);
	}
	else
	{
		if (exec->fd_out != STDOUT_FILENO)
			close(exec->fd_out);
		if (file->type == OUTFILE)
			exec->fd_out = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == APPEND)
			exec->fd_out
				= open(file->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (exec->fd_out == -1)
			exe_err1_open(errno, file->path);
		exe_dup2_close(exec->fd_out, STDOUT_FILENO);
	}
}
