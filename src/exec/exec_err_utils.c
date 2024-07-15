/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:26:50 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/15 13:59:49 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_err1_open(int err_no, char *file)
{
	int		fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("%s: %s: %s\n", P_NAME, file, strerror(err_no));
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
}

void	exe_err2_pipe(int err_no)
{
	int		fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("%s: %s\n", P_NAME, strerror(err_no));
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
	exit(2);
}

void	exe_err3_fork(int err_no)
{
	int		fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("%s: %s\n", P_NAME, strerror(err_no));
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
	exit(3);
}

void	exe_err4_exec(char *path, int err_no)
{
	int		fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (exe_is_abs_path(path) == 1)
		ft_printf("%s: %s: %s\n", P_NAME, path, strerror(err_no));
	else
		ft_printf("%s: %s: command not found\n", P_NAME, path);
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
}

int	exe_check_fdio(int fd_in, int fd_out, char *file)
{
	if (fd_in == -1 || fd_out == -1)
	{
		exe_err1_open(errno, file);
		return (1);
	}
	return (0);
}
