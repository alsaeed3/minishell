# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 15:33:15 by alsaeed           #+#    #+#              #
#    Updated: 2023/12/25 22:03:16 by alsaeed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	../minishell

SRCS =	convert_tabs_to_spc.c error_parts_2.c error_parts.c \
		find_infiles_heredocs_num.c find_inputs_chars_num.c \
		find_outfiles_appends_num.c find_parts_num.c malloc_infile_heredocs.c del_excess_spcs.c\
		quotes.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS=.c:.o))

CFLAGS = -Wall -Werror -Wextra -lreadline

LIBFT_DIR = ../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(LIBFT_LIB) $(NAME)

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)
	@echo "minishell Compilation: \033[1;32OK\n\033[0m"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

norm:
	norminette

clean:
	@make clean -C $(LIBFT_DIR)
	@if [ -e $(OBJS_DIR) ]; then \
		rm -rf $(OBJS_DIR); \
		echo "minishell Clean: \033[32mOK\n\033[0m"; \
	fi
 
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@if [ -e $(NAME) ]; then \
		rm -f $(NAME); \
		echo "minishell Full-Clean: \033[32mOK\n\033[0m"; \
	fi

re: fclean all

.PHONY: all clean fclean re