/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/14 08:54:41 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_create_pipe(int *fd_out, int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		exe_err2_pipe(errno);
	close(*fd_out);
	/* redirect fd_out to pipe_w, pipe_r will be set after redirection*/
	*fd_out = fd_pipe[1];
}

int	exe_redir_fdio(int *fd_in, int *fd_out, int pipe[2], t_exec *exec)
{
	if (*fd_in == -1 || *fd_out == -1)
	{
		if (exec->next)
		{
			exe_dup2_close(pipe[0], STDIN_FILENO);
			*fd_in = pipe[0];
		}
		return (1);
	}
	else
	{
		exe_dup2_close(*fd_in, STDIN_FILENO);
		exe_dup2_close(*fd_out, STDOUT_FILENO);
		if (exec->next)
			*fd_in = pipe[0];
	}
	return (0);
}

void	exe_do_child(t_ctx *ctx, t_exec *exec, int fd_in)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exe_err3_fork(errno);
	else if (!pid)
	{
		if (exec->next)
			close(fd_in);
		if (bi_is_builtin(exec->cmd) == 1)
		{
			if (exec->here_doc == 1)
				unlink("here_doc");
			exit(bi_do_builtin(ctx, exec->cmd, exec->args));
		}
		else if (exe_do_exec(ctx, exec->cmd, exec->args) < 0)
			exit(1);
		exit(0);
	}
}

void	exe_dup2_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

int	exe_is_abs_path(char *file)
{
	while (*file)
	{
		if (*file++ == '/')
			return (1);
	}
	return (0);
}
