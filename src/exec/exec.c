/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/08 13:48:35 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_here_doc(char *file, char *eof)
{
	int		fd_in;
	char	*limiter;
	char	*line;

	fd_in = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_in == -1)
		return (-1);
	limiter = ft_strjoin(eof, "\n");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(fd_in, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(limiter);
	close(fd_in);
	return (open(file, O_RDONLY));
}

int		handle_infile(t_filenames *redirs)
{
	int		fd_in;
	int		fd_tmp;

	while (redirs)
	{
		if (redirs->type == INFILE)
		{
			fd_tmp = open(redirs->path, O_RDONLY);
			dup2(fd_tmp, fd_in);
			close(fd_tmp);
		}
		else if (redirs->type == HEREDOC)
		{
			fd_tmp = init_here_doc("here_doc", redirs->path);
			dup2(fd_tmp, fd_in);
			close(fd_tmp);
		}
		if (fd_in == -1)
			return (-1);
		redirs = redirs->next;
	}
	return (fd_in);
}

void	set_init_input(int *fd_in, t_filenames *redirs)
{
	int			i;
	t_filenames	*tmp;

	i = 0;
	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == INFILE || tmp->type == HEREDOC)
			i++;
		tmp = tmp->next;
	}
	if (!i)
		return ;
	else
	{
		close(*fd_in);
		*fd_in = handle_infile(redirs);
	}
	return (fd_in);
}

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
			dup2(fd_pipe[1], fd_out);  // redirect fd_out to pipe_w
			close(fd_pipe[1]);
			fd_in = fd_pipe[0]; //set fd_in for the next exec
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
	// printf("exec\n");
	return (0);
}
