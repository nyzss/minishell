/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:09:45 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/11 10:20:23 by tsuchen          ###   ########.fr       */
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

int	bi_cd(t_args *args)
{
	int	size_args;

	size_args = ft_lstsize(args);
	if (!size_args)
		chdir(getenv("HOME"));
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
		return (1);
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

	exit_code = 0;
	if (args)
		exit_code = ft_atoi(args->value);
	exit(exit_code);
}

int	bi_env(t_args *args, char **env)
{
	if (args)
	{
		write(STDERR_FILENO, "minishell: env: too many arguments\n", 36);
		return (1);
	}
	while (*env)
	{
        if (bi_is_equal(*env))
            printf("%s\n", *env);
		env++;
	}
	return (0);
}
