/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:09:45 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/17 19:15:10 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_echo(t_args *args)
{
	int	n_flag;

	n_flag = 0;
	if (args && !ft_strcmp(args->value, "-n"))
	{
		n_flag = 1;
		args = args->next;
	}
	while (args)
	{
		printf("%s", args->value);
		if (args->next)
			printf("%s", " ");
		args = args->next;
	}
	if (!n_flag)
		printf("%s", "\n");
	return (0);
}

int	bi_cd(t_ctx *ctx, t_args *args)
{
	int		size_args;
	char	*cwd;
	t_env	*home;

	size_args = arg_lstsize(args);
	if (size_args > 1)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("chdir: error retrieving current directory: getcwd: cannot access parent directories");
	home = ms_getenv("HOME", ctx->envp);
	if (!size_args && home != NULL && home->value != NULL)
		chdir(home->value);
	else if ((!size_args && home && !home->value) || (!size_args && !home))
		return (bi_err_cd(errno, "HOME"), free(cwd), 1);
	else if (chdir(args->value) < 0)
	{
		bi_err_cd(errno, args->value);
		return (free(cwd), 1);
	}
	if (bi_update_pwd(ctx, cwd))
		return (free(cwd), 1);
	return (free(cwd), 0);
}

int	bi_pwd(t_args *args)
{
	char	*cwd;

	if (args && *(args->value) == '-' && (ft_strcmp(args->value, "-L")
			&& ft_strcmp(args->value, "-P")))
	{
		bi_err_pwd(args->value);
		return (2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd: error retrieving current directory: getcwd: cannot access parent directories");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	bi_exit(t_ctx *ctx, t_args *args)
{
	int		exit_code;

	exit_code = 0;
	if (args)
		exit_code = bi_check_exitcode(args->value);
	exe_close_all(ctx, NULL);
	ms_free_all(ctx);
	exit(exit_code);
}

int	bi_env(t_ctx *ctx, t_args *args)
{
	t_env	*tmp;

	tmp = ctx->envp;
	if (args)
	{
		bi_err_env(args->value);
		return (127);
	}
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->id, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
