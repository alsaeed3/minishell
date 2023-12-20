# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 20:07:00 by alsaeed           #+#    #+#              #
#    Updated: 2023/12/20 15:36:03 by alsaeed          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(NAME):	all

all:
	@make all -C parsing

clean: 
	@make clean -C parsing
 
fclean: clean
	@make fclean -C parsing

re: fclean all