/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tabs_to_spc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:38:22 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/04 17:40:34 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	*conv_tabs2spcs(char *str)
{
	int		i;
	int		j;
	char	trigger;
	int		len;
	char	*ret;

	trigger = -1;
	i		= -1;
	j		= -1;
	len = ft_strlen(str);
	ret = malloc(sizeof(char *) * (len + 1));
	while (++i < len)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			ret[++j] = str[i];
			trigger = str[i];
			while (++i < len)
			{
				if (str[i] == trigger)
				{
					ret[++j] = str[i];
					break;
				}
				ret[++j] = str[i];
			}
		}
		else if (str[i] == '\t')
		{
			ret[++j] = ' ';
			while (str[i + 1] == '\t')
				i++;
		}
		else 
			ret[++j] = str[i];
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