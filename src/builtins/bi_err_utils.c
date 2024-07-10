/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_err_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:12:57 by tsuchen           #+#    #+#             */
/*   Updated: 2024/07/10 17:23:33 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bi_err_cd(int err_no, char *file)
{
    int     fd_tmp;

    fd_tmp = dup(STDOUT_FILENO);
    dup2(STDERR_FILENO, STDOUT_FILENO);
    ft_printf("%s: cd: %s: %s\n", P_NAME, file, strerror(err_no));
    exe_dup2_close(fd_tmp, STDOUT_FILENO);
}