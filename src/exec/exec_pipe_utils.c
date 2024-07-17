/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/17 13:39:21 by okoca            ###   ########.fr       */
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
	int		fd_pipe[2];

	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	if (exec->next != NULL)
		exe_create_pipe(fd_pipe);
	signal(SIGINT, sig_exec);
	ctx->pids[ctx->pid_count] = fork();
	if (ctx->pids[ctx->pid_count] == -1)
		exe_err3_fork(errno);
	else if (!ctx->pids[ctx->pid_count])
		exe_do_child2(ctx, exec, fd_pipe);
	else
		dup2(fd_pipe[0], STDIN_FILENO);
	exe_close_all(NULL, fd_pipe);
}

// this is going to unlink all in case of a builtin?
void	exe_do_child2(t_ctx *ctx, t_exec *exec, int fd_pipe[])
{
	int	exit_code;

	exit_code = 0;
	signal(SIGQUIT, SIG_DFL);
	if (exec->next && exec->fd_out == STDOUT_FILENO)
		dup2(fd_pipe[1], STDOUT_FILENO);
	if (exe_init_fdio(exec))
	{
		exe_close_all(ctx, fd_pipe);
		ms_free_all(ctx);
		exit(EXIT_FAILURE);
	}
	exe_close_all(ctx, fd_pipe);
	if (bi_is_builtin(exec->cmd))
	{
		exit_code = bi_do_builtin(ctx, exec->cmd, exec->args);
		ms_free_all(ctx);
		exit(exit_code);
	}
	else if (exe_do_exec(ctx, exec->cmd, exec->args) < 0)
	{
		ms_free_all(ctx);
		exit(COMMAND_NOT_FOUND);
	}
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
