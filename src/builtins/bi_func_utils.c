/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:09:45 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/12 15:06:01 by tsuchen          ###   ########.fr       */
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

int	bi_cd(t_args *args, t_env *env)
{
	int	size_args;

	size_args = arg_lstsize(args);
	if (!size_args)
		chdir(ms_getenv("HOME", env));
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

int	bi_exit(t_args *args)
{
	int		exit_code;
	char	*tmp;

	exit_code = 0;
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
	exit(exit_code);
}

int	bi_env(t_args *args, t_env *env)
{
	if (args)
	{
		bi_err_env(args->value);
		return (127);
	}
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->id, env->value);
		env = env->next;
	}
	return (0);
}
