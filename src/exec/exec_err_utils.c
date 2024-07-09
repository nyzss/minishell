/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:26:50 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/09 19:49:59 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err1_open(int err_no, char *file, t_exec *exec)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("%s: %s: %s\n", exec->cmd, file, strerror(err_no));
}

void	ft_err2_pipe(int err_no, t_exec *exec)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("%s: %s\n", exec->cmd, strerror(err_no));
	exit(2);
}

void	ft_err3_fork(int err_no, t_exec *exec)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("%s: %s\n", exec->cmd, strerror(err_no));
	exit(3);
}