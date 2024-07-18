/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:35 by okoca             #+#    #+#             */
/*   Updated: 2024/07/18 19:13:47 by tsuchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env	t_env;

/* Built-in handler */
int		bi_do_builtin(t_ctx *ctx, char *cmd, t_args *args);
int		bi_is_builtin(char *cmd);

/* Built-in Functions */
int		bi_echo(t_args *args);
int		bi_cd(t_ctx *ctx, t_args *args);
int		bi_pwd(t_args *args);
int		bi_exit(t_ctx *ctx, t_args *args);
int		bi_env(t_ctx *ctx, t_args *args);
int		bi_export(t_ctx *ctx, t_args *args);
int		bi_unset(t_ctx *ctx, t_args *args);

/* helper functions builtins */
int		bi_print_export(t_env *env);
int		bi_add_var(char *value, t_env **env);
int		bi_del_var(char *value, t_env **env);
int		bi_check_id(char *id);
int		bi_check_exitcode(char *value);
int		bi_update_pwd(t_ctx *ctx, char *value);
int		bi_is_nflag(char *flag);

/* error utils */
void	bi_err_cd(int err_no, char *file);
void	bi_err_pwd(char *option);
int		bi_err_export(char *var);
void	bi_err_exit(char *val);
void	bi_err_env(char *file);

#endif
