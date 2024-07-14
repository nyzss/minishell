/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/14 17:18:44 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_create_pipe(int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		exe_err2_pipe(errno);
}

void	exe_close_all(t_ctx *ctx, int pipe[])
{
	if (ctx)
	{
		if (ctx->def_in != -1)
			close(ctx->def_in);
		if (ctx->def_out != -1)
			close(ctx->def_out);
	}
	if (pipe)
	{
		if (pipe[0] != -1)
			close(pipe[0]);
		if (pipe[1] != -1)
			close(pipe[1]);
	}
}

void	exe_do_child(t_ctx *ctx, t_exec *exec)
{
	pid_t	pid;
	int		fd_pipe[2];

	exe_create_pipe(fd_pipe);
	pid = fork();
	if (pid == -1)
		exe_err3_fork(errno);
	else if (!pid)
	{
		exe_init_fdio(exec);
		if (exec->next != NULL)
			dup2(fd_pipe[1], STDOUT_FILENO);
		exe_close_all(ctx, fd_pipe);
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
	else
		dup2(fd_pipe[0], STDIN_FILENO);
	exe_close_all(NULL, fd_pipe);
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
