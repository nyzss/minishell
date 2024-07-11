/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:56 by okoca             #+#    #+#             */
/*   Updated: 2024/07/11 15:18:19 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <ncurses.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"

# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "builtins.h"
# include "builder.h"

# define P_NAME "minishell"
# define BLUE_A    "\033[1;34m"
# define MAGENTA_A "\033[1;35m"
# define CYAN_A    "\033[1;36m"

# define ESC_F "\001"
# define ESC_S "\002"
# define C_RESET "\033[0m"

# define PROMPT "\001\033[1;36m\002minishell >$ \001\033[0m\002"

typedef struct s_ctx
{
	int				def_in;
	int				def_out;
	t_exec			*exec;
	char			**env;
	unsigned int	exit_code;
}	t_ctx;

t_ctx	*ms_init_ctx(char **envp);

void	ms_free_all(t_ctx *ctx);

int		ms_check_line(char *line);

void	ms_clear(t_exec *exec, t_token *token);

char	**ms_env_dup(char **envp);

void	*ms_free_double(char **value);

char	*ms_getenv(char *path, char **envp);

#endif