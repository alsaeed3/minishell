# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 15:33:15 by alsaeed           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/02/21 15:45:57 by alsaeed          ###   ########.fr        #
=======
#    Updated: 2024/02/21 16:17:57 by alsaeed          ###   ########.fr        #
>>>>>>> main
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
		expand_dlr_sign.c \
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
		export_utils.c \
		exit.c \
		env.c \
		unset.c \
		data_init.c \
		redirections_utils.c \
		redirections.c \
		exec_utils.c \
		pipe.c \
		close_fds.c \
		free.c \
		signal.c \
		ft_error.c \
		exec_utils2.c \
		execute_pipe.c 

OBJS_DIR = parsing/objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJSX_DIR = execution/objs/
OBJSX = $(addprefix $(OBJSX_DIR), $(SRCSX:.c=.o))
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline -lncurses

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(LIBFT_LIB) $(NAME)																				

$(OBJS_DIR)%.o: parsing/%.c
	@mkdir -p $(OBJS_DIR)
	@cc $(CFLAGS) -c $< -o $@
	
$(OBJSX_DIR)%.o: execution/%.c
	@mkdir -p $(OBJSX_DIR)
	@cc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS) $(OBJSX) main.c
	@cc $(CFLAGS) $(OBJS) $(OBJSX) $(LIBFT_LIB) main.c -o $(NAME) $(LDFLAGS)
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