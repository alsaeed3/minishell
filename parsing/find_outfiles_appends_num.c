/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outfiles_appends_num.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:11:01 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/08 16:59:51 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	*find_outfiles_appends_num(char *cmd_line, int parts_num)
{
	int		i;
	int		j;
	int		len;
	char	trigger;
	int		*outfiles_appends_num;

	i = -1;
	j = 0;
	len = ft_strlen(cmd_line);
	outfiles_appends_num = ft_calloc(parts_num ,sizeof(int));
	while (++i < len)
	{
		if (cmd_line[i] == '|')
			j++;
		if (cmd_line[i] == '\'' || cmd_line[i] == '"')
		{
			trigger = cmd_line[i];
			while (++i < len)
			{
				if (cmd_line[i] == trigger)
					break;
			}
		}
		if ((i <= len - 1) && cmd_line[i] == '>' && cmd_line[i + 1] != '>' && (i == 0 || cmd_line[i - 1] != '>'))
			outfiles_appends_num[j]++;
		else if ((i <= len - 2) && cmd_line[i] == '>' && cmd_line[i + 1] == '>' && cmd_line[i + 2] != '>' && (i == 0 || cmd_line[i - 1] != '>'))
			outfiles_appends_num[j]++;
	}
	return (outfiles_appends_num);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		char *input = readline("$> ");
// 		char *outdup = ft_strdup(input);
// 		free(input);
// 		int		parts_num = find_parts_num(outdup);
// 		int *outfiles_appends_num = find_outfiles_appends_num(outdup, parts_num);
// 		for (int i = 0; i < parts_num; i++)
// 			printf("outfiles_appends_num[%d] = %d\n", i, outfiles_appends_num[i]);
// 		free (outfiles_appends_num);
// 	}
// }