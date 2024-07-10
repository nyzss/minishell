/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:01:00 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/10 11:44:37 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exe_create_pipe(int *fd_out, int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		exe_err2_pipe(errno);
	close(*fd_out);
	*fd_out = fd_pipe[1];	// redirect fd_out to pipe_w, pipe_r will be set after redirection
}

int		exe_init_fdio(int *fd_in, int *fd_out, t_exec *exec, int fd_stdin)
{
	//check here_doc first
	if (exe_is_here_doc(exec, fd_stdin))
		exec->here_doc = 1;
	if (exe_handle_files(fd_in, fd_out, exec))
		return (1);
	return (0);
}

int		exe_is_here_doc(t_exec *exec, int fd_stdin)
{
	t_filenames	*tmp;
	int			i;

	i = 0;
	tmp = exec->redirs;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			exe_init_here_doc("here_doc", tmp->path, fd_stdin);
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

int		exe_handle_files(int *fd_in, int *fd_out, t_exec *exec)
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
		if (exe_check_fdio(fd_in, fd_out, tmp->path))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		exe_check_fdio(int *fd_in, int *fd_out, char *file)
{
	if (*fd_in == -1)
	{
		exe_err1_open(errno, file);
		return (1);
	}
	if (*fd_out == -1)
	{
		exe_err1_open(errno, file);
		return (1);
	}
	return (0);
}

int		exe_redirect_fdio(int *fd_in, int *fd_out, int fd_pipe[2], t_exec *exec)
{
	if (*fd_in == -1 || *fd_out == -1)
	{
		if (exec->next)
		{
			exe_dup2_close(fd_pipe[0], STDIN_FILENO);
			*fd_in = fd_pipe[0];
		}
		return (1);
	}
	else
	{
		exe_dup2_close(*fd_in, STDIN_FILENO);
		exe_dup2_close(*fd_out, STDOUT_FILENO);
		if (exec->next)
			*fd_in = fd_pipe[0];
	}
	return (0);
}

void    exe_do_child(t_exec *exec, char **env, int fd_in)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exe_err3_fork(errno);
	else if (!pid)
	{
		if (exec->next)
			close(fd_in);
		if (exe_do_exec(exec->cmd, exec->args, env) < 0)
			exit(1);
	}
}

int		exe_do_exec(char *cmd, t_args *args, char **env)
{
	char	*path;
	char	**cmd;

	path = exe_get_path(cmd, env);
	if (!path)
		return (-1);
	cmd = exe_get_cmd(cmd, args);
	if (!cmd)
	{
		free(path);
		return (-1);
	}
	if (execve(path, cmd, env) == -1)
	{
		exe_err4_exec(path, errno);
		exe_free_all(cmd);
		free(path);
		return (-1);
	}
	exe_free_all(cmd);
	free(path);
	return (0);
}

char	*exe_get_path(char *file, char **env)
{
	char	**paths;
	char	*exec;

	if (!env || exe_is_abs_path(file) == 1)
		return (ft_strdup(file));
	paths = exe_get_allpaths(env);
	if (!paths)
		return (ft_strdup(file));
	exec = exe_get_exec(paths, file);
	exe_free_all(paths);
	return (exec);
}

char	*exe_get_exec(char **paths, char *file)
{
	char	*exec;
	char	*path;
	int		i;
	
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(path[i], "/");
		if (!path)
			return (NULL);
		exec = ft_strjoin(path, file);
		free(path);
		if (!exec)
			return (NULL);
		if (!access(exec, X_OK | F_OK))
			return (exec);
		free(exec);
	}
	return (NULL);
}

char	**exe_get_allpaths(char **env)
{
	int		i;
	char	*path_all;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path_all = ft_strtrim(env[i], "PATH=");
			if (!path_all)
				return (NULL);
			paths = ft_split(path_all, ':');
			free(path_all);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	**exe_get_cmd(char *cmd, t_args *args)
{
	char	**cmds;
	int		arg_size;
	int		i;
	
	i = -1;
	arg_size = ft_lstsize(args);
	cmds = (char **)malloc((arg_size + 2) * sizeof(char *));
	if (!cmds)
		return (NULL);
	while (++i < arg_size + 1)
	{
		if (!i)
			cmds[i] = ft_strdup(cmd);
		else
			cmds[i] = ft_strdup(args->value);
		if (!cmds[i])
		{
			exe_free_all(cmds);
			return (NULL);
		}
	}
	cmds[i] = NULL;
	return (cmds);
}

void	exe_dup2_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
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

int		exe_is_abs_path(char *file)
{
	while (*file)
	{
		if (*file++ == '/')
			return (1);
	}
	return (0);
}