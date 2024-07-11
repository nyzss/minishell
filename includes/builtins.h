/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/11 10:21:13 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* Built-in handler */
int bi_do_builtin(char *cmd, t_args *args, char **env);
int bi_is_builtin(char *cmd);

/* Built-in Functions */
int bi_echo(t_args *args);
int bi_cd(t_args *args);
int bi_pwd(t_args *args);
int bi_exit(t_args *args);
int	bi_env(t_args *args, char **env);
int bi_export(t_args *args, char **env);
int bi_unset(t_args *args, char **env);

/* error utils */
void    bi_err_cd(int err_no, char *file);
void    bi_err_pwd(char *option);
int bi_is_equal(char *var);

#endif