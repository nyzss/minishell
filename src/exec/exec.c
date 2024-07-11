/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/11 18:50:22 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_ctx *ctx)
{
	int		fd_in;
	int		fd_out;
	int		exec_no;

	exe_get_stdfds(ctx);
	exec_no = ft_lstsize((void *)ctx->exec);
	if (exec_no == 1)
		exec_1(ctx, exec_no, &fd_in, &fd_out);
	else
		exec_2(ctx, exec_no, &fd_in, &fd_out);
	exe_reset_stdfds(ctx);
	return (0);
}

int	exec_1(t_ctx *ctx, int exec_no, int *fd_in, int *fd_out)
{
	*fd_in = dup(ctx->def_in);
	*fd_out = dup(ctx->def_out);
	if (exe_init_fdio(fd_in, fd_out, ctx->exec, ctx->def_in))
		exec_no--;
	if (!exec_no)
		return (1);
	exe_dup2_close(*fd_in, STDIN_FILENO);
	exe_dup2_close(*fd_out, STDOUT_FILENO);
	if (bi_is_builtin(ctx->exec->cmd) == 1)
	{
		if (ctx->exec->here_doc == 1)
			unlink("here_doc");
		exec_no--;
		ctx->exit_code = bi_do_builtin(ctx->exec->cmd,
			ctx->exec->args, &ctx->env);
	}
	else
	{
		exe_do_child(ctx->exec, ctx->env, *fd_in);
		if (ctx->exec->here_doc == 1)
			unlink("here_doc");
	}
	exe_wait_all(exec_no, &ctx->exit_code);
	return (0);
}

int	exec_2(t_ctx *ctx, int exec_no, int *fd_in, int *fd_out)
{
	int		fd_pipe[2];

	*fd_in = dup(ctx->def_in);// initiate infile
	while (ctx->exec)
	{
		*fd_out = dup(ctx->def_out);// initiate outfile
		// create pipe first if needed
		if (ctx->exec->next)
			exe_create_pipe(fd_out, fd_pipe);
		// go through files and set input and output, stop whenever fd == -1
		if (exe_init_fdio(fd_in, fd_out, ctx->exec, ctx->def_in))
			exec_no--;
		// check fdio and redirect to STDIN & OUT; if all good then exec child
		if (!exe_redir_fdio(fd_in, fd_out, fd_pipe, ctx->exec))
			exe_do_child(ctx->exec, ctx->env, *fd_in);
		if (ctx->exec->here_doc == 1)
			unlink("here_doc");
		ctx->exec = ctx->exec->next;
	}
	exe_wait_all(exec_no, &ctx->exit_code);
	return (0);
}

void	exe_get_stdfds(t_ctx *ctx)
{
	ctx->def_in = dup(STDIN_FILENO);
	ctx->def_out = dup(STDOUT_FILENO);
}

void	exe_reset_stdfds(t_ctx *ctx)
{
	dup2(ctx->def_in, STDIN_FILENO);
	dup2(ctx->def_out, STDOUT_FILENO);
	close(ctx->def_in);
	close(ctx->def_out);
}

void	exe_wait_all(int rep, unsigned int *exit_code)
{
	int		status;

	while (rep--)
	{
		if (wait(&status))
		{
			if (WIFEXITED(status))
				*exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*exit_code = WTERMSIG(status);
		}
	}
}

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
// 	exec_no = ft_lstsize((void *)ctx->exec);
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
