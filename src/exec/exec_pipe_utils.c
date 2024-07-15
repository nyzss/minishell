/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/15 13:22:10 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_create_pipe(int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		exe_err2_pipe(errno);
}

void	exe_do_child(t_ctx *ctx, t_exec *exec)
{
	pid_t	pid;
	int		fd_pipe[2];

	exe_create_pipe(fd_pipe);
	signal(SIGINT, sig_exec);
	pid = fork();
	if (pid == -1)
		exe_err3_fork(errno);
	else if (!pid)
		exe_do_child2(ctx, exec, fd_pipe);
	else
		dup2(fd_pipe[0], STDIN_FILENO);
	exe_close_all(NULL, fd_pipe);
}

void	exe_do_child2(t_ctx *ctx, t_exec *exec, int fd_pipe[])
{
	if (exe_init_fdio(exec))
	{
		exe_close_all(ctx, fd_pipe);
		exit(1);
	}
	if (exec->next)
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
