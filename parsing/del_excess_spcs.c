/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_excess_spcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:24:39 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/20 16:51:19 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	*delete_excess_spcs(char *cmd_line)
{
	int		i;
	int		j;
	int		len;
	char	trigger;
	char	*ret;

	len = ft_strlen(cmd_line);
	ret = ft_calloc(len + 1, sizeof(char));
	j = -1;
	i = -1;
	while (++i < len)
	{
		if (cmd_line[i] == '\"' || cmd_line[i] == '\'')
		{
			ret[++j] = cmd_line[i];
			trigger = cmd_line[i++];
			while (cmd_line[i] != trigger)
				ret[++j] = cmd_line[i++];
		}
		if (cmd_line[i] == ' ' && cmd_line[i + 1] == ' ')
		{
			ret[++j] = ' ';
			while (cmd_line[i] == ' ')
				i++;
		}
		ret[++j] = cmd_line[i];
	}
	ret[++j] = '\0';
	return (ret);
}

// int main(void)
// {
// 	int	i;
// 	char *str;
// 	while(1)
// 	{
// 		char *input = readline("$> ");
// 		str = delete_excess_spcs(input);
// 		free(input);
// 		printf("%s\n", str);
// 		free(str);
// 	}
// }