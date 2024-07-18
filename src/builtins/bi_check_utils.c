/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_check_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:42:10 by okoca             #+#    #+#             */
/*   Updated: 2024/07/18 19:06:37 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_check_id(char *id)
{
	int	i;

	i = 0;
	if (!*id)
		return (0);
	while (id[i])
	{
		if (i == 0 && ft_isalpha(id[i]) == 0 && id[i] != '_')
			return (0);
		if (ft_isalnum(id[i]) == 0 && id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	bi_check_exitcode(char *value)
{
	char	*tmp;
	char	*tmp2;

	tmp = value;
	if ((*tmp == '+' || *tmp == '-') && *(tmp + 1))
		tmp++;
	while (*tmp)
	{
		if (!ft_isdigit(*tmp++))
			return (1);
	}
	tmp = value;
	if (*tmp == '+')
		tmp++;
	tmp2 = ft_ltoa(ft_atol(tmp));
	if (ft_strcmp(tmp, tmp2))
	{
		free(tmp2);
		return (1);
	}
	free(tmp2);
	return (0);
}

int	bi_update_pwd(t_ctx *ctx, char *value)
{
	t_env	*old_pwd;
	t_env	*pwd;
	char	*cwd_new;
	char	*raw;
	char	*raw2;

	cwd_new = getcwd(NULL, 0);
	old_pwd = ms_getenv("OLDPWD", ctx->envp);
	pwd = ms_getenv("PWD", ctx->envp);
	if (pwd && cwd_new)
	{
		raw2 = ft_strjoin("PWD=", cwd_new);
		if (!raw2 || bi_add_var(raw2, &ctx->envp))
			return (free(cwd_new), 1);
		free(raw2);
	}
	if (old_pwd && value)
	{
		raw = ft_strjoin("OLDPWD=", value);
		if (!raw || bi_add_var(raw, &ctx->envp))
			return (free(cwd_new), 1);
		free(raw);
	}
	free(cwd_new);
	return (0);
}

int	bi_is_nflag(char *flag)
{
	if (!ft_strncmp(flag, "-n", 2))
		flag += 2;
	else
		return (1);
	while (*flag)
	{
		if (*flag++ != 'n')
			return (1);
	}
	return (0);
}
