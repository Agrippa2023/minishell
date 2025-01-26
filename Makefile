# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/28 18:05:54 by aouichou          #+#    #+#              #
#    Updated: 2023/03/23 02:02:48 by aouichou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC_D		= srcs/
OBJ_D		= objs/
INC_D		= include/

SRC			= main.c				\
			init.c					\
			env.c					\
			error.c					\
			tools.c					\
			execute.c				\
			expander.c				\
			free.c					\
			lexer.c					\
			parser.c				\
			prompt.c				\
			signals.c				\
			split_check_quotes.c	\
			builtins.c				\
			ft_exit.c				\
			unquote.c				\
			fill_list.c				\
			heredoc.c				\
			get_fd.c				\
			cmds_split_trim.c		\
			pipex.c					\
			export.c				\
			cd.c					\
			env_tools.c				\
			tools2.c				\
			split_keep.c			\
			count_redir.c			\
			per_history.c			\

OBJ			= $(addprefix $(OBJ_D), $(SRC:.c=.o))
FLAGS		= -g -Wall -Werror -Wextra #-fsanitize=address 
INCS		= -I $(INC_D) -I libft/ -lreadline -L ./libft/ -lft

all: $(OBJ_D) $(NAME)

$(OBJ_D):
	@mkdir -p $@

$(NAME): $(OBJ)
	@make -C libft
	gcc $(FLAGS) $^ -o $@ $(INCS)

$(OBJ_D)%.o: $(SRC_D)%.c
	gcc $(FLAGS) -o $@ -c $< $(INCS)

clean:
	rm -rf $(OBJ_D)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus