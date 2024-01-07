# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 11:36:52 by habu-zua          #+#    #+#              #
#    Updated: 2023/12/16 12:10:40 by habu-zua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	 = libft.a
SRCSDIR	 = srcs
OBJSDIR  = objs
INCLUDES = inc

SRCS  = libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c\
		libft/ft_isprint.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c \
		libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_lstadd_back.c \
		libft/ft_lstadd_front.c libft/ft_lstclear.c libft/ft_lstdelone.c \
		libft/ft_lstiter.c libft/ft_lstlast.c libft/ft_lstmap.c libft/ft_lstnew.c\
		libft/ft_lstsize.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_memchr.c \
		libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c \
		libft/ft_malloc.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strlcpy.c \
		libft/ft_strndup.c libft/ft_strmapi.c libft/ft_strnstr.c libft/ft_strtrim.c \
		libft/ft_tolower.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strlcat.c \
		libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strrchr.c libft/ft_substr.c \
		libft/ft_toupper.c libft/ft_strcmp.c libft/ft_atoi.c libft/ft_itoa.c \
		libft/ft_strjoin_free.c
SRCS  += libft/get_next_line.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	@ar rcs $(NAME) $(OBJS)	
	@echo "\033[32m$@ is ready\033[0m"

$(OBJS) : $(OBJSDIR)/%.o:$(SRCSDIR)/%.c $(INCLUDES)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o  $@

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re