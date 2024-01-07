/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_parts_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:45:33 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/07 18:32:50 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	find_parts_num(char *cmd_line)
{
	int		i;
	int		parts_num;
	t_bool	quo_trigger;
	char	quo_char;
	int		len;

	quo_trigger = FALSE;
	quo_char = '\0';
	parts_num = 1;
	len = (int)ft_strlen(cmd_line);
	i = -1;
	while (++i < len)
	{
		if ((cmd_line[i] == '"' || cmd_line[i] == '\'') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
		}
		else if ((cmd_line[i] == quo_char) && quo_trigger)
			quo_trigger = false;
		if (cmd_line[i] == '|' && !quo_trigger)
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