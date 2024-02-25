# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 14:48:47 by alsaeed           #+#    #+#              #
#    Updated: 2024/02/17 20:20:22 by alsaeed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libft.a

SRCS =			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
				ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
				ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
				ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_calloc.c \
				ft_strdup.c ft_atoi.c ft_substr.c ft_strjoin.c ft_strtrim.c \
				ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_bzero.c \
				ft_strchr.c ft_strdup.c ft_strtrim.c ft_memcpy.c ft_isspace.c \
				ft_memset.c ft_substr.c ft_calloc.c ft_strlcpy.c ft_strdup_nonl.c \
				ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_deallocate_lst.c ft_putchar.c ft_putstr.c ft_putnbr.c print_hex.c \
				print_pointer.c print_undec.c ft_printf.c get_next_line.c \
				get_next_line_utils.c ft_free_array.c ft_isspace_str.c ft_space_arg.c \
				ft_array_size.c ft_get_array.c ft_strjoin_sp.c
OBJS_DIR =		src/objs/
OBJS = 			$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

CFLAGS =		-Wall -Wextra -Werror -g3
RM = 			rm -f
ARFLAGS = 		ar -rcs

all: 			$(NAME)

$(OBJS_DIR)%.o: src/%.c
	@mkdir -p $(OBJS_DIR)
	@cc $(CFLAGS) -c $< -o $@

$(NAME): 		$(OBJS)
	@$(ARFLAGS) $(NAME) $(OBJS)
	@echo "libft Compiled : \033[1;32mOK\033[0m"

clean:
	@if [ -e $(OBJS_DIR) ]; then \
		rm -rf $(OBJS_DIR); \
		echo "libft Clean : \033[32mOK\033[0m"; \
	fi

fclean: 		clean
	@if [ -e $(NAME) ]; then \
		$(RM) $(NAME); \
		echo "libft Full-Clean : \033[32mOK\033[0m"; \
	fi
re: 			fclean all

.PHONY:			all clean fclean re