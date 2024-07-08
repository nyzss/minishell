/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:23:56 by okoca             #+#    #+#             */
/*   Updated: 2024/07/08 13:54:37 by okoca            ###   ########.fr       */
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

// ----------------------- LEXER -----------------------

typedef enum e_token_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE,
	STRING,
	COMMAND,
	FILENAME,
	ARGUMENT
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

// ----------------------- EXEC -----------------------

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}	t_args;

typedef struct s_filenames
{
	char				*path;
	t_token_type		type;
	struct s_filenames	*next;
}	t_filenames;

typedef struct s_exec
{
	char			*cmd;
	t_args			*args;
	t_filenames		*redirs;
	struct s_exec	*next;
}	t_exec;

typedef struct s_ctx
{
	int			def_in;
	int			def_out;
	t_exec		*exec;
	char		**env;
}	t_ctx;

void	builtins(void);
void	exec(void);
void	lexer(void);
void	parser(void);

void	todo(char *what_to_do);

t_ctx	*init_ctx(char **envp);

void	free_all(t_ctx *ctx);

#endif