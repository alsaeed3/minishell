NAME = minishell
CC = cc
CFLAGS = #-Wall -Werror -Wextra 
INCS_DIR = includes/
INCS = main.h
LIBFT= libft.a

SRC = main.c ft_free.c ft_getpath.c ft_print_cmd.c ft_trim_input.c
OBJ = $(SRC:.c=.o)

%.o: %.c 
	$(CC) $(CFLAGS) -I $(INCS_DIR)/INCS -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib
	$(CC) $(CFLAGS) $(OBJ) lib/$(LIBFT) -lreadline -o $(NAME)

clean:
	make -C lib clean
	rm -f $(OBJ)

fclean: clean
	make -C lib fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

