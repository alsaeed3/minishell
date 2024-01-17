/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tabs_to_spc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:38:22 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/09 15:54:12 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	*conv_tabs2spcs(char *cmd_line)
{
	int		i;
	int		j;
	char	trigger;
	int		len;
	char	*ret;

	trigger = -1;
	i		= -1;
	j		= -1;
	len = ft_strlen(cmd_line);
	ret = malloc(sizeof(char *) * (len + 1));
	while (++i < len)
	{
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
		{
			ret[++j] = cmd_line[i];
			trigger = cmd_line[i];
			while (++i < len)
			{
				if (cmd_line[i] == trigger)
				{
					ret[++j] = cmd_line[i];
					break;
				}
				ret[++j] = cmd_line[i];
			}
		}
		else if (cmd_line[i] == '\t')
		{
			ret[++j] = ' ';
			while (cmd_line[i + 1] == '\t')
				i++;
		}
		else 
			ret[++j] = cmd_line[i];
	}
	ret[++j] = '\0';
	return(ret);
}

// int main(void)
// {
// 	char *str;
// 	char *hell;

// 	while (1)
// 	{
// 		str = readline("> ");
// 		hell = conv_tabs2spcs(str);
// 		free(str);
// 		printf("%s\n", hell);
// 		free(hell);
// 	}
// 	return (0);
// }