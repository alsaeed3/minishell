# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 15:33:15 by alsaeed           #+#    #+#              #
#    Updated: 2024/01/21 17:26:26 by alsaeed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	convert_tabs_to_spc.c \
		quotes.c \
		del_excess_spcs.c \
		error_pipes_2.c \
		error_pipes.c \
		find_infiles_heredocs_num.c \
		find_inputs_chars_num.c \
		find_outfiles_appends_num.c \
		find_outputs_chars_num.c \
		find_parts_num.c \
		malloc_infile_heredocs.c \
		mallocing_in_redir_file_names.c \
		malloc_outfiles_appends.c \
		mallocing_out_redir_file_names.c \
		tokenize_in_redir.c \
		tokenize_out_redir.c \
		convert_redir_to_spc.c \
		split_commands.c \
		get_envs.c \
		expand_dollar2env.c \
		handle_heredoc.c \
		parse.c 

SRCSX = exec_delegate.c execute.c ft_getpath.c ft_free.c\
		cd.c cd_utils.c echo.c pwd.c\
		export.c export_utils.c\
		exit.c env.c unset.c \
		data_init.c redirections.c exec_utils.c\
		pipe.c close_fds.c


OBJS_DIR = parsing/objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJSX_DIR = execution/objs/
OBJSX = $(addprefix $(OBJSX_DIR), $(SRCSX:.c=.o))
CFLAGS = -Wall -Wextra -Werror -I inc -g3 -fsanitize=address
LDFLAGS = -lreadline

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(LIBFT_LIB) $(NAME)

$(OBJS_DIR)%.o: parsing/%.c
	@mkdir -p $(OBJS_DIR)
	@clang $(CFLAGS) -c $< -o $@
	
$(OBJSX_DIR)%.o: execution/%.c
	@mkdir -p $(OBJSX_DIR)
	@clang $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS) $(OBJSX)
	@clang $(CFLAGS) $(OBJS) $(OBJSX) $(LIBFT_LIB) main.c -o $(NAME) $(LDFLAGS)
	@echo "minishell Compiled: \033[1;32mOK\n\033[0m"

$(LIBFT_LIB):
	@make -sC $(LIBFT_DIR)

norm:
	norminette

clean:
	@make clean -sC $(LIBFT_DIR)
	@if [ -e $(OBJS_DIR) ]; then \
		rm -rf $(OBJS_DIR); \
		echo "minishell-parsing Clean: \033[32mOK\n\033[0m"; \
	fi
	@if [ -e $(OBJSX_DIR) ]; then \
		rm -rf $(OBJSX_DIR); \
		echo "minishell-execution Clean: \033[32mOK\n\033[0m"; \
	fi
 
fclean: clean
	@make fclean -sC $(LIBFT_DIR)
	@if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
		echo "minishell Full-Clean: \033[32mOK\n\033[0m"; \
	fi

re: fclean all

.PHONY: all clean fclean re