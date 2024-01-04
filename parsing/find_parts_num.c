/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_parts_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:45:33 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/04 20:59:55 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	find_parts_num(char *str)
{
	int	i;
	int	parts_num;

	i = -1;
	parts_num = 1;
	while (++i < (int)ft_strlen(str))
	{
		if (str[i] == '|')
			parts_num++;
	}
	return (parts_num);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		char *input = readline("$> ");
// 		int char_num = find_parts_num(input);
// 		free (input);
// 		printf("%d\n", char_num);
// 	}
// 	return (0);	
// }