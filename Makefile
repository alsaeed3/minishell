# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 15:33:15 by alsaeed           #+#    #+#              #
#    Updated: 2024/02/14 17:01:34 by alsaeed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	cmds_utils.c \
		cnv_rdr2spc_utils.c \
		convert_redir_to_spc.c \
		convert_tabs_to_spc.c \
		del_excess_spcs.c \
		dollar_utils_1.c \
		dollar_utils_2.c \
		error_pipes.c \
		error_pipes_2.c \
		expand_dollar2env.c \
		find_parts_num.c \
		find_rdr_chars.c \
		find_rdr_num.c \
		get_envs.c \
		handle_heredoc_utils.c \
		handle_heredoc.c \
		hold_rdr_names.c \
		malloc_rdr_names.c \
		parse.c \
		quotes.c \
		split_commands.c \
		tokenize_redir.c \
		loop_utils.c \
		loop_utils_2.c \
		free_utils.c
		

SRCSX = exec_delegate.c \
		execute.c \
		cd.c \
		cd_utils.c \
		echo.c \
		pwd.c \
		export.c \
		export_utils.c\
		exit.c \
		env.c \
		unset.c \
		data_init.c \
		redirections.c \
		exec_utils.c \
		pipe.c \
		close_fds.c \
		free.c \
		signal.c \
		ft_error.c\
		exp_dlr_sgn2.c\
		execute_pipe.c\
		ft_strreplace.c\

OBJS_DIR = parsing/objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJSX_DIR = execution/objs/
OBJSX = $(addprefix $(OBJSX_DIR), $(SRCSX:.c=.o))
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline -lncurses

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(LIBFT_LIB) $(NAME)																				

$(OBJS_DIR)%.o: parsing/%.c
	@mkdir -p $(OBJS_DIR)
	@clang $(CFLAGS) -c $< -o $@
	
$(OBJSX_DIR)%.o: execution/%.c
	@mkdir -p $(OBJSX_DIR)
	@clang $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS) $(OBJSX) main.c
	@clang $(CFLAGS) $(OBJS) $(OBJSX) $(LIBFT_LIB) main.c -o $(NAME) $(LDFLAGS)
	@echo "minishell Compiled: \033[1;32mOK\033[0m"

$(LIBFT_LIB):
	@make -sC $(LIBFT_DIR)

norm:
	norminette

clean:
	@make clean -sC $(LIBFT_DIR)
	@if [ -e $(OBJS_DIR) ]; then \
		rm -rf $(OBJS_DIR); \
		echo "minishell-parsing Clean: \033[32mOK\033[0m"; \
	fi
	@if [ -e $(OBJSX_DIR) ]; then \
		rm -rf $(OBJSX_DIR); \
		echo "minishell-execution Clean: \033[32mOK\033[0m"; \
	fi
 
fclean: clean
	@make fclean -sC $(LIBFT_DIR)
	@if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
		echo "minishell Full-Clean: \033[32mOK\033[0m"; \
	fi

re: fclean all

.PHONY: all clean fclean re valgrind