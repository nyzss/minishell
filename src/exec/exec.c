/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/17 09:33:28 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_ctx *ctx)
{
	if (ctx->exec_count == 0)
		return (0);
	exe_set_stdfds(ctx, 0);
	exec_2(ctx);
	exe_set_stdfds(ctx, 1);
	return (0);
}

int	exec_2(t_ctx *ctx)
{
	t_exec	*tmp;

	tmp = ctx->exec;
	if (tmp->next == NULL && bi_is_builtin(tmp->cmd))
	{
		if (exe_init_fdio(tmp))
		{
			ctx->exit_code = 1;
			return (1);
		}
		if (bi_is_builtin(tmp->cmd) == 2)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		exe_unlink_all(ctx);
		ctx->exit_code = bi_do_builtin(ctx, tmp->cmd, tmp->args);
		return (0);
	}
	while (tmp)
	{
		exe_do_child(ctx, tmp);
		ctx->pid_count++;
		tmp = tmp->next;
	}
	exe_wait_all(ctx);
	return (0);
}

void	exe_set_stdfds(t_ctx *ctx, int mode)
{
	if (!mode)
	{
		ctx->def_in = dup(STDIN_FILENO);
		ctx->def_out = dup(STDOUT_FILENO);
	}
	else
	{
		exe_dup2_close(ctx->def_in, STDIN_FILENO);
		exe_dup2_close(ctx->def_out, STDOUT_FILENO);
	}
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

// printf("SIGNALLED: %d\n", WIFSIGNALED(status));
void	exe_wait_all(t_ctx *ctx)
{
	int		status;
	int		i;

	i = 0;
	while (i < ctx->pid_count)
	{
		if (waitpid(ctx->pids[i], &(status), 0))
		{
			if (WIFEXITED(status))
			{
				g_signals.signal_code = EXIT_SUCCESS;
				ctx->exit_code = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				g_signals.signal_code = SIGINT_EXIT_CODE;
				ctx->exit_code = WTERMSIG(status);
			}
		}
		i++;
	}
	exe_unlink_all(ctx);
}

// int	exec_1(t_ctx *ctx, int exec_no)
// {
// 	*fd_in = dup(ctx->def_in);
// 	*fd_out = dup(ctx->def_out);
// 	if (exe_init_fdio(fd_in, fd_out, ctx->exec, ctx->def_in))
// 		exec_no--;
// 	if (!exec_no)
// 		return (1);
// 	exe_dup2_close(*fd_in, STDIN_FILENO);
// 	exe_dup2_close(*fd_out, STDOUT_FILENO);
// 	if (bi_is_builtin(ctx->exec->cmd) == 1)
// 	{
// 		if (ctx->exec->here_doc == 1)
// 			unlink("here_doc");
// 		exec_no--;
// 		ctx->exit_code = bi_do_builtin(ctx, ctx->exec->cmd,
// 			ctx->exec->args);
// 	}
// 	else
// 	{
// 		exe_do_child(ctx, ctx->exec, *fd_in);
// 		if (ctx->exec->here_doc == 1)
// 			unlink("here_doc");
// 	}
// 	exe_wait_all(exec_no, &(ctx->exit_code));
// 	return (0);
// }

/* Previous exec main */
// int	exec(t_ctx *ctx)
// {
// 	int		fd_in; //fd_in for each exec
// 	int		fd_out; //fd_out for each exec
// 	int		fd_pipe[2];
// 	int		exec_no;

// 	// create tmp i/o for iterations
// 	get_stdfds(ctx);
// 	fd_in = dup(ctx->def_in); // initiate infile
// 	fd_out = dup(ctx->def_out); // initiate outfile
// 	// cast to void pointer just for compilation
// 	exec_no = br_lstsize(ctx->exec);
// 	// iterate through executables
// 	while (ctx->exec)
// 	{
// 		// set initial input
// 		set_init_input(&fd_in, ctx->exec->redirs, ctx->def_in);
// 		// redirect input
// 		ft_dup2_close(fd_in, STDIN_FILENO);
// 		//set output
// 		if (ctx->exec->next)
// 			create_pipe(&fd_in, &fd_out, fd_pipe, ctx->exec);
// 		set_init_output(&fd_out, ctx->exec->redirs);
// 		// redirect output
// 		ft_dup2_close(fd_out, STDOUT_FILENO);
// 		do_child(ctx->exec, ctx->env, &ctx->exit_code);
// 		ctx->exec = ctx->exec->next;
// 	}
// 	// wait all child process
// 	wait_all(exec_no);
// 	// restore fdin and fdout to default
// 	reset_stdfds(ctx);
// 	return (0);
// }
