/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:33 by okoca             #+#    #+#             */
/*   Updated: 2024/07/12 18:57:24 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

int	bi_do_builtin(char *cmd, t_args *args, t_env **env)
{
	if (!ft_strcmp(cmd, "echo"))
		return (bi_echo(args));
	else if (!ft_strcmp(cmd, "cd"))
		return (bi_cd(args, *env));
	else if (!ft_strcmp(cmd, "pwd"))
		return (bi_pwd(args));
	else if (!ft_strcmp(cmd, "export"))
		return (bi_export(args, env));
	else if (!ft_strcmp(cmd, "unset"))
		return (bi_unset(args, env));
	else if (!ft_strcmp(cmd, "env"))
		return (bi_env(args, *env));
	else if (!ft_strcmp(cmd, "exit"))
		return (bi_exit(args));
	else
		return (0);
}

int	bi_export(t_args *args, t_env **env)
{
	int	exit_code;

	exit_code = 0;
	if (!args)
	{
		if (bi_print_export(*env))
			exit_code = 1;
	}
	else
	{
		while (args)
		{
			if (bi_add_var(args->value, env))
				exit_code = 1;
			args = args->next;
		}
	}
	return (exit_code);
}

int	bi_unset(t_args *args, t_env **env)
{
	if (!args)
		return (0);
	else
	{
		while (args)
		{
			if (bi_del_var(args->value, env))
				return (1);
			args = args->next;
		}
	}
	return (0);
}
