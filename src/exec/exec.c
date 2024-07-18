/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/18 20:12:26 by okoca            ###   ########.fr       */
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
		{
			close(ctx->def_in);
			ctx->def_in = -1;
		}
		if (ctx->def_out != -1)
		{
			close(ctx->def_out);
			ctx->def_out = -1;
		}
	}
	if (pipe)
	{
		if (pipe[0] != -1)
		{
			close(pipe[0]);
			pipe[0] = -1;
		}
		if (pipe[1] != -1)
		{
			close(pipe[1]);
			pipe[1] = -1;
		}
	}
}

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
				g_signals.signal_code = 0;
				ctx->exit_code = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					exe_err_coredump(ctx->pids[i]);
				g_signals.signal_code = SIGNAL_OFFSET + WTERMSIG(status);
			}
		}
		i++;
	}
	exe_unlink_all(ctx);
}
