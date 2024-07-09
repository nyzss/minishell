/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/09 08:46:17 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_ctx *ctx)
{
	int		fd_in; //fd_in for each exec
	int		fd_out; //fd_out for each exec
	int		fd_pipe[2];
	int		exec_no;
	int		i;

	// create tmp i/o for iterations
	get_stdfds(ctx);
	fd_in = dup(ctx->def_in); // initiate infile
	fd_out = dup(ctx->def_out); // initiate outfile
	// cast to void pointer just for compilation
	exec_no = ft_lstsize((void *)ctx->exec);
	i = 0;
	// iterate through executables
	while (ctx->exec)
	{
		// set initial input
		set_init_input(&fd_in, ctx->exec->redirs);
		// redirect input
		ft_dup2_close(fd_in, STDIN_FILENO);
		//set output
		if (ctx->exec->next)
		{
			if (pipe(fd_pipe) == -1)
				//ft_err2_pipe(errno);
			close(fd_out);
			fd_out = fd_pipe[1]; // redirect fd_out to pipe_w
			fd_in = fd_pipe[0]; // set fd_in to pipe_r
		}
		set_init_output(&fd_out, ctx->exec->redirs);
		// redirect output
		ft_dup2_close(fd_out, STDOUT_FILENO);
		do_child(ctx->exec, ctx->env, &ctx->exit_code);
		ctx->exec = ctx->exec->next;
	}
	// wait all child process
	while (i++ < exec_no)
		wait(NULL);
	// restore fdin and fdout to default
	reset_stdfds(ctx);
	return (0);
}