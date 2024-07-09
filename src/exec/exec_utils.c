/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/09 19:49:31 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_stdfds(t_ctx *ctx)
{
	ctx->def_in = dup(STDIN_FILENO);
	ctx->def_out = dup(STDOUT_FILENO);
}

void	reset_stdfds(t_ctx *ctx)
{
	dup2(ctx->def_in, STDIN_FILENO);
	dup2(ctx->def_out, STDOUT_FILENO);
	close(ctx->def_in);
	close(ctx->def_out);
}

void	create_pipe(int *fd_out, int fd_pipe[2], t_exec *exec)
{
	if (pipe(fd_pipe) == -1)
		ft_err2_pipe(errno, exec);
	close(*fd_out);
	*fd_out = fd_pipe[1];	// redirect fd_out to pipe_w, pipe_r will be set after redirection
}

int		init_fdio(int *fd_in, int *fd_out, t_exec *exec, int fd_stdin)
{
	//check here_doc first
	if (is_here_doc(exec, fd_stdin))
		exec->here_doc = 1;
	if (handle_files(fd_in, fd_out, exec))
		return (1);
	return (0);
}

int		is_here_doc(t_exec *exec, int fd_stdin)
{
	t_filenames	*tmp;
	int			i;

	i = 0;
	tmp = exec->redirs;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			init_here_doc("here_doc", tmp->path, fd_stdin);
			free(tmp->path);
			tmp->path = ft_strdup("here_doc");
			tmp->type = INFILE;
			i++;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	init_here_doc(char *file, char *eof, int fd_stdin)
{
	int		fd;
	char	*limiter;
	char	*line;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	limiter = ft_strjoin(eof, "\n");
	line = get_next_line(fd_stdin);
	while (line)
	{
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd_stdin);
	}
	free(limiter);
	close(fd);
}

int		handle_files(int *fd_in, int *fd_out, t_exec *exec)
{
	t_filenames	*tmp;

	tmp = exec->redirs;
	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			close(*fd_in);
			*fd_in = open(tmp->path, O_RDONLY);
		}
		else if (tmp->type == OUTFILE)
		{
			close(*fd_out);
			*fd_out = open(tmp->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (tmp->type == APPEND)
		{
			close(*fd_out);
			*fd_out = open(tmp->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (check_fdio(fd_in, fd_out, tmp->path, exec))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		check_fdio(int *fd_in, int *fd_out, char *file, t_exec *exec)
{
	if (*fd_in == -1)
	{
		ft_err1_open(errno, file, exec);
		return (1);
	}
	if (*fd_out == -1)
	{
		ft_err1_open(errno, file, exec);
		return (1);
	}
	return (0);
}

int		redirect_fdio(int *fd_in, int *fd_out, int fd_pipe[2], t_exec *exec)
{
	if (*fd_in == -1 || *fd_out == -1)
	{
		if (exec->next)
		{
			dup2_close(fd_pipe[0], STDIN_FILENO);
			*fd_in = fd_pipe[0];
		}
		return (1);
	}
	else
	{
		dup2_close(*fd_in, STDIN_FILENO);
		dup2_close(*fd_out, STDOUT_FILENO);
		if (exec->next)
			*fd_in = fd_pipe[0];
	}
	return (0);
}

void    do_child(t_exec *exec, char **env, unsigned int *exit_code)
{
    (void)exec;
    (void)env;
    (void)exit_code;
}

void	dup2_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}