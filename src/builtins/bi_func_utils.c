/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:09:45 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/18 19:09:26 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_echo(t_args *args)
{
	int	n_flag;

	n_flag = 0;
	while (args && !bi_is_nflag(args->value))
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
	int		siz;
	char	*cwd;
	t_env	*home;

	siz = arg_lstsize(args);
	if (siz > 1)
		return (ft_putstr_fd("minishell: cd: too many arguments\n",
				STDERR_FILENO), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("minishell: cd: error retrieving current directory");
	home = ms_getenv("HOME", ctx->envp);
	if ((!siz || !ft_strcmp(args->value, "--")) && home && home->value)
		chdir(home->value);
	else if ((!siz || !ft_strcmp(args->value, "--")) && (!home || !home->value))
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
		perror("minishell: pwd: error retrieving current directory");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	bi_exit(t_ctx *ctx, t_args *args)
{
	int		exit_code;
	int		siz;

	siz = arg_lstsize(args);
	if (siz > 1 && !bi_check_exitcode(args->value))
		return (ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO), 1);
	exit_code = 0;
	if (args && !bi_check_exitcode(args->value))
		exit_code = ft_atoi(args->value);
	else if (args && bi_check_exitcode(args->value))
	{
		bi_err_exit(args->value);
		exit_code = 2;
	}
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
