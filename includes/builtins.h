/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/10 17:25:50 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_bi
{
    char    *cmd;
    int     (*func)(t_args *);
}   t_bi;

void	builtins(void);
int bi_do_exec(char *cmd, t_args *args, char **env);
int bi_is_builtin(char *cmd);

/* Built-in Functions */
int bi_echo(t_args *args);
int bi_cd(t_args *args);

/* error utils*/
void    bi_err_cd(int err_no, char *file);


#endif