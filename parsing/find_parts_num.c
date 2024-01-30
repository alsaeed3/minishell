/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_parts_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:45:33 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/30 19:49:07 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	find_parts_num(char *str)
{
	int		i;
	int		parts_num;
	t_bool	quo_trigger;
	char	quo_char;
	int		len;

	quo_trigger = FALSE;
	quo_char = '\0';
	parts_num = 1;
	len = (int)ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quo_trigger)
		{
			quo_char = str[i];
			quo_trigger = TRUE;
		}
		else if ((str[i] == quo_char) && quo_trigger)
			quo_trigger = false;
		if (str[i] == '|' && !quo_trigger)
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