/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/08 19:39:10 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_ctx *ctx)
{
	int		tmpin;
	int		tmpout;
	int		fd_in; //fd_in for each pipe
	int		fd_out; //fd_out for each pipe
	int		fd_pipe[2];
	int		exec_no;
	int		i;

	// create tmp i/o for iterations
	tmpin = dup(ctx->def_in);
	tmpout = dup(ctx->def_out);
	fd_in = dup(tmpin); // initiate infile
	fd_out = dup(tmpout); // initiate outfile
	exec_no = ft_lstsize(ctx->exec);
	i = 0;
	// iterate through executables
	while (ctx->exec)
	{
		// set initial input
		set_init_input(&fd_in, ctx->exec->redirs);
		// redirect input
		dup2(fd_in, ctx->def_in);
		close(fd_in);
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
		dup2(fd_out, ctx->def_out);
		close(fd_out);
		do_child(ctx->exec, ctx->env, &ctx->exit_code);
		ctx->exec = ctx->exec->next;
	}
	// wait all child process
	while (i++ < exec_no)
		wait(NULL);
	// restore fdin and fdout to default
	dup2(tmpin, ctx->def_in);
	dup2(tmpout, ctx->def_out);
	close(tmpin);
	close(tmpout);
	return (0);
}
