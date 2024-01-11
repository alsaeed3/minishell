/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outfiles_appends_num.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:11:01 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/11 21:07:36 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	*find_outfiles_appends_num(char *cmd_line)
{
	int		parts_num;
	int		i;
	int		j;
	int		len;
	t_bool	quo_trigger;
	char	quo_char;
	int		*outfiles_appends_num;

	i = -1;
	j = 0;
	len = ft_strlen(cmd_line);
	parts_num = find_parts_num(cmd_line);
	outfiles_appends_num = ft_calloc(parts_num ,sizeof(int));
	quo_trigger = FALSE;
	quo_char = '\0';
	while (++i < len)
	{
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
		}
		else if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == '|' && !quo_trigger && j < parts_num)
			j++;
		if (i < len - 1 && (cmd_line[i] == '>' && cmd_line[i + 1] != '>' && (i == 0 || cmd_line[i - 1] != '>')) && !quo_trigger)
			outfiles_appends_num[j]++;
		else if (i < len - 1 && (cmd_line[i] == '>' && cmd_line[i + 1] == '>') && !quo_trigger)
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