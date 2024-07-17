/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:33:54 by okoca             #+#    #+#             */
/*   Updated: 2024/07/17 13:38:39 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_err_coredump(int pid)
{
	int		fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("[%d]: Quit (core dumped)\n", pid);
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
}
