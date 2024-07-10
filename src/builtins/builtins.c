/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:34:33 by okoca             #+#    #+#             */
/*   Updated: 2024/07/10 17:30:19 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(void)
{
	printf("builtins\n");
}

int	bi_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
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
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 35);
	else
	{
		if (chdir(args->value) < 0)
			bi_err_cd(errno, args->value);
	}
	return (0);
}

int	bi_pwd(t_args *args)
{
	
}