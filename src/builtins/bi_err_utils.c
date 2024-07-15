/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_err_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:12:57 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/15 15:11:53 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_err_cd(int err_no, char *file)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (file && ft_strcmp(file, "HOME") == 0)
		printf("%s: cd: %s not set\n", P_NAME, file);
	else
		printf("%s: cd: %s: %s\n", P_NAME, file, strerror(err_no));
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
}

void	bi_err_pwd(char *option)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: pwd: %s: invalid option\n", P_NAME, option);
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
}

int	bi_err_export(char *var)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: export: %s: not a valid identifier\n", P_NAME, var);
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
	return (1);
}

void	bi_err_exit(char *val)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: exit: %s: numeric argument required\n", P_NAME, val);
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
}

void	bi_err_env(char *file)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("env: %s: No such file or directory\n", file);
	exe_dup2_close(fd_tmp, STDOUT_FILENO);
}
