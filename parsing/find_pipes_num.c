/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_pipes_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:45:33 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/21 14:55:00 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	find_pipes_num(char *str)
{
	int	i;
	int	pipes_num;

	i = -1;
	pipes_num = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '|')
			pipes_num++;
	}
	pipes_num++;
	return (pipes_num);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		char *input = readline("$> ");
// 		int char_num = find_pipes_num(input);
// 		free (input);
// 		printf("%d\n", char_num);
// 	}
// 	return (0);	
// }