/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fdio_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:55:08 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/14 17:10:54 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_init_fdio(t_exec *exec)
{
	if (exe_is_here_doc(exec))
		exec->here_doc = 1;
	if (exe_handle_files(exec))
		return (1);
	return (0);
}

int	exe_is_here_doc(t_exec *exec)
{
	t_filenames	*tmp;
	int			i;

	i = 0;
	tmp = exec->redirs;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			signal(SIGINT, sig_handle_heredoc);
			exe_init_here_doc("here_doc", tmp->path, STDIN_FILENO);
			free(tmp->path);
			tmp->path = ft_strdup("here_doc");
			tmp->type = INFILE;
			i++;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	exe_init_here_doc(char *file, char *eof, int fd_stdin)
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

int	exe_handle_files(t_exec *exec)
{
	t_filenames	*tmp;

	tmp = exec->redirs;
	while (tmp)
	{
		if (tmp->type == INFILE)
		{
			if (exec->fd_in != STDIN_FILENO)
				close(exec->fd_in);
			exec->fd_in = open(tmp->path, O_RDONLY);
			exe_dup2_close(exec->fd_in, STDIN_FILENO);
		}
		else if (tmp->type == OUTFILE)
		{
			if (exec->fd_out != STDOUT_FILENO)
				close(exec->fd_out);
			exec->fd_out = open(tmp->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			exe_dup2_close(exec->fd_out, STDOUT_FILENO);
		}
		else if (tmp->type == APPEND)
		{
			if (exec->fd_out != STDOUT_FILENO)
				close(exec->fd_out);
			exec->fd_out = open(tmp->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			exe_dup2_close(exec->fd_out, STDOUT_FILENO);
		}
		if (exe_check_fdio(exec->fd_in, exec->fd_out, tmp->path))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	exe_check_fdio(int fd_in, int fd_out, char *file)
{
	if (fd_in == -1)
	{
		exe_err1_open(errno, file);
		return (1);
	}
	if (fd_out == -1)
	{
		exe_err1_open(errno, file);
		return (1);
	}
	return (0);
}
