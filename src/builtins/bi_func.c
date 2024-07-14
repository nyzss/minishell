/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:33 by okoca             #+#    #+#             */
/*   Updated: 2024/07/14 09:34:03 by okoca            ###   ########.fr       */
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

int	bi_do_builtin(t_ctx *ctx, char *cmd, t_args *args)
{
	if (!ft_strcmp(cmd, "echo"))
		return (bi_echo(args));
	else if (!ft_strcmp(cmd, "cd"))
		return (bi_cd(ctx, args));
	else if (!ft_strcmp(cmd, "pwd"))
		return (bi_pwd(args));
	else if (!ft_strcmp(cmd, "export"))
		return (bi_export(ctx, args));
	else if (!ft_strcmp(cmd, "unset"))
		return (bi_unset(ctx, args));
	else if (!ft_strcmp(cmd, "env"))
		return (bi_env(ctx, args));
	else if (!ft_strcmp(cmd, "exit"))
		return (bi_exit(ctx, args));
	else
		return (0);
}

int	bi_export(t_ctx *ctx, t_args *args)
{
	int	exit_code;

	exit_code = 0;
	if (!args)
	{
		if (bi_print_export(ctx->envp))
			exit_code = 1;
	}
	else
	{
		while (args)
		{
			if (bi_add_var(args->value, &(ctx->envp)))
				exit_code = 1;
			args = args->next;
		}
	}
	return (exit_code);
}

int	bi_unset(t_ctx *ctx, t_args *args)
{
	if (!args)
		return (0);
	else
	{
		while (args)
		{
			if (bi_del_var(args->value, &(ctx->envp)))
				return (1);
			args = args->next;
		}
	}
	return (0);
}
