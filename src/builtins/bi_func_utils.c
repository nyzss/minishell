/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:09:45 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/15 13:33:55 by okoca            ###   ########.fr       */
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
	t_env	*home;

	size_args = arg_lstsize(args);
	home = ms_getenv("HOME", ctx->envp);
	if (!size_args && home != NULL && home->value != NULL)
		chdir(home->value);
	else if ((!size_args && home && !home->value) || (!size_args && !home))
		return (bi_err_cd(errno, "HOME"), 1);
	else if (size_args > 1)
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	else
	{
		if (chdir(args->value) < 0)
		{
			bi_err_cd(errno, args->value);
			return (1);
		}
	}
	return (0);
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
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	bi_exit(t_ctx *ctx, t_args *args)
{
	int		exit_code;
	char	*tmp;

	exit_code = 0;
	printf("exit\n");
	if (args)
	{
		exit_code = ft_atoi(args->value);
		tmp = args->value;
		while (*tmp)
		{
			if (!ft_isdigit(*tmp++))
			{
				bi_err_exit(args->value);
				exit_code = 2;
				break ;
			}
		}
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
