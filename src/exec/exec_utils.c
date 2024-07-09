/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/09 08:47:38 by okoca            ###   ########.fr       */
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

	// init at -1 for compilation
	fd_in = -1;
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

int		handle_outfile(t_filenames *redirs)
{
	int		fd_out;
	int		fd_tmp;

	// init at -1 for compilation
	fd_out = -1;
	while (redirs)
	{
		if (redirs->type == OUTFILE)
		{
			fd_tmp = open(redirs->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd_tmp, fd_out);
			close(fd_tmp);
		}
		else if (redirs->type == APPEND)
		{
			fd_tmp = open(redirs->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd_tmp, fd_out);
			close(fd_tmp);
		}
		if (fd_out == -1)
			return (-1);
		redirs = redirs->next;
	}
	return (fd_out);
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
	if (i)
	{
		close(*fd_in);
		*fd_in = handle_infile(redirs);
	}
}

void	set_init_output(int *fd_out, t_filenames *redirs)
{
	int			i;
	t_filenames	*tmp;

	i = 0;
	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == OUTFILE || tmp->type == APPEND)
			i++;
		tmp = tmp->next;
	}
	if (i)
	{
		close(*fd_out);
		*fd_out = handle_infile(redirs);
	}
}

void    do_child(t_exec *exec, char **env, unsigned int *exit_code)
{
    (void)exec;
    (void)env;
    (void)exit_code;
}

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

void	ft_dup2_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

void	create_pipe(int	*fd_in, int *fd_out, int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		//ft_err2_pipe(errno);
	close(*fd_out);
	*fd_out = fd_pipe[1];	// redirect fd_out to pipe_w
	*fd_in = fd_pipe[0];	// set fd_in to pipe_r
}

void	wait_all(int exec_no)
{
	int		i;

	i = 0;
	while (i++ < exec_no)
		wait(NULL);
}