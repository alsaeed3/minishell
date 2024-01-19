# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 20:07:00 by alsaeed           #+#    #+#              #
#    Updated: 2024/01/14 20:18:16 by alsaeed          ###   ########.fr        #
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