/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 14:18:48 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_ctx *ctx)
{
	int		fd_in; //fd_in for each exec
	int		fd_out; //fd_out for each exec
	int		fd_pipe[2];
	int		exec_no;

	// create tmp i/o for iterations
	get_stdfds(ctx);
	fd_in = dup(ctx->def_in); // initiate infile
	fd_out = dup(ctx->def_out); // initiate outfile
	// cast to void pointer just for compilation
	exec_no = ft_lstsize((void *)ctx->exec);
	// iterate through executables
	while (ctx->exec)
	{
		// set initial input
		set_init_input(&fd_in, ctx->exec->redirs, ctx->def_in);
		// redirect input
		ft_dup2_close(fd_in, STDIN_FILENO);
		//set output
		if (ctx->exec->next)
			create_pipe(&fd_in, &fd_out, fd_pipe, ctx->exec);
		set_init_output(&fd_out, ctx->exec->redirs);
		// redirect output
		ft_dup2_close(fd_out, STDOUT_FILENO);
		do_child(ctx->exec, ctx->env, &ctx->exit_code);
		ctx->exec = ctx->exec->next;
	}
	// wait all child process
	wait_all(exec_no);
	// restore fdin and fdout to default
	reset_stdfds(ctx);
	return (0);
}