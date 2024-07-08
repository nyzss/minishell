# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okoca <okoca@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 11:20:19 by okoca             #+#    #+#              #
#    Updated: 2024/07/08 17:35:18 by okoca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SRCS_M	=	main.c

SRCS_BT	=	builtins.c

SRCS_EX =	exec.c

SRCS_LEX =	lexer.c \
			tokens.c \
			lex_helper.c

SRCS_PAR =	parser.c

SRCS_UTI =	utils.c

SRC = src/

BUILTINS_PATH	= src/builtins/
EXEC_PATH	= src/exec/
LEXER_PATH	= src/lexer/
PARSER_PATH	= src/parser/
UTILS_PATH	= src/utils/

SRCS		= ${addprefix ${SRC}, ${SRCS_M}}\
		  $(addprefix $(BUILTINS_PATH), $(SRCS_BT)) \
		  $(addprefix $(EXEC_PATH), $(SRCS_EX)) \
		  $(addprefix $(LEXER_PATH), $(SRCS_LEX)) \
		  $(addprefix $(PARSER_PATH), $(SRCS_PAR)) \
		  $(addprefix $(UTILS_PATH), $(SRCS_UTI)) \

# F_PATH		= src/

# SRCS		= $(addprefix $(F_PATH), $(SRCS_F))

OBJS		= $(SRCS:.c=.o)

HEAD		= includes/

CFLAGS		= -Wall -Wextra -Werror

CC			= cc

LIBFT_PATH	= libft/
LIBFT_H_PATH	= libft/includes/
LIBFT		= $(LIBFT_PATH)libft.a

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEAD) -I$(LIBFT_H_PATH) -c $< -o $@

clean: libft-clean root-clean

libft-clean:
	$(MAKE) -C $(LIBFT_PATH) clean

root-clean:
	rm -f $(OBJS)

fclean: libft-fclean root-fclean

libft-fclean:
	$(MAKE) -C $(LIBFT_PATH) fclean

root-fclean: root-clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re libft libft-clean libft-fclean root-clean root-fclean