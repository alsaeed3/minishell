# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 15:33:15 by alsaeed           #+#    #+#              #
#    Updated: 2024/01/21 17:28:34 by habu-zua         ###   ########.fr        #
=======
#    By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 15:33:15 by alsaeed           #+#    #+#              #
#    Updated: 2024/02/21 16:17:57 by alsaeed          ###   ########.fr        #
>>>>>>> main
#                                                                              #
# **************************************************************************** #

NAME =	minishell

<<<<<<< HEAD
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
		parse.c \

SRCSX = exec_delegate.c execute.c \
		cd.c cd_utils.c echo.c pwd.c\
		export.c export_utils.c\
		exit.c env.c unset.c \
		data_init.c redirections.c exec_utils.c\
		pipe.c close_fds.c free.c signal.c \

=======
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
>>>>>>> main

OBJS_DIR = parsing/objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJSX_DIR = execution/objs/
OBJSX = $(addprefix $(OBJSX_DIR), $(SRCSX:.c=.o))
<<<<<<< HEAD
CFLAGS = -Wall -Wextra -Werror -I inc -g3 -fsanitize=address
LDFLAGS = -lreadline
=======
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline -lncurses
>>>>>>> main

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

<<<<<<< HEAD
all: $(LIBFT_LIB) $(NAME)

$(OBJS_DIR)%.o: parsing/%.c
	@mkdir -p $(OBJS_DIR)
	@gcc $(CFLAGS) -c $< -o $@
	
$(OBJSX_DIR)%.o: execution/%.c
	@mkdir -p $(OBJSX_DIR)
	@gcc $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS) $(OBJSX) main.c
	@gcc $(CFLAGS) $(OBJS) $(OBJSX) $(LIBFT_LIB) main.c -o $(NAME) $(LDFLAGS)
	@echo "minishell Compiled: \033[1;32mOK\n\033[0m"
=======
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
>>>>>>> main

$(LIBFT_LIB):
	@make -sC $(LIBFT_DIR)

norm:
	norminette

clean:
	@make clean -sC $(LIBFT_DIR)
	@if [ -e $(OBJS_DIR) ]; then \
		rm -rf $(OBJS_DIR); \
<<<<<<< HEAD
	fi
	@if [ -e $(OBJSX_DIR) ]; then \
		rm -rf $(OBJSX_DIR); \
		echo "minishell Clean: \033[32mOK\n\033[0m"; \
=======
		echo "minishell-parsing Clean: \033[32mOK\033[0m"; \
	fi
	@if [ -e $(OBJSX_DIR) ]; then \
		rm -rf $(OBJSX_DIR); \
		echo "minishell-execution Clean: \033[32mOK\033[0m"; \
>>>>>>> main
	fi
 
fclean: clean
	@make fclean -sC $(LIBFT_DIR)
	@if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
<<<<<<< HEAD
		echo "minishell Full-Clean: \033[32mOK\n\033[0m"; \
=======
		echo "minishell Full-Clean: \033[32mOK\033[0m"; \
>>>>>>> main
	fi

re: fclean all

<<<<<<< HEAD
.PHONY: all clean fclean re
=======
.PHONY: all clean fclean re valgrind
>>>>>>> main
