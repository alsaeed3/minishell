# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 20:07:00 by alsaeed           #+#    #+#              #
#    Updated: 2024/01/06 02:53:57 by alsaeed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(NAME):	all

all:
	@make all -sC parsing

clean: 
	@make clean -sC parsing
 
fclean: clean
	@make fclean -sC parsing

re: fclean all