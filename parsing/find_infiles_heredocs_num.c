/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles_heredocs_num.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:47:49 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/22 13:35:25 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	*find_infiles_heredocs_num(char *cmd_line)
{
	int		parts_num;
	int		i;
	int		j;
	int		len;
	t_bool	quo_trigger;
	char	quo_char;
	int		*infiles_heredocs_num;

	i = -1;
	j = 0;
	len = ft_strlen(cmd_line);
	parts_num = find_parts_num(cmd_line);
	infiles_heredocs_num = ft_calloc(parts_num ,sizeof(int));
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
		if (i < len - 1 && (cmd_line[i] == '<' && cmd_line[i + 1] != '<' && (i == 0 || cmd_line[i - 1] != '<')) && !quo_trigger)
			infiles_heredocs_num[j]++;
		else if (i < len - 1 && (cmd_line[i] == '<' && cmd_line[i + 1] == '<') && !quo_trigger)
			infiles_heredocs_num[j]++;
	}
	return (infiles_heredocs_num);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		int *infiles_heredocs_num;
// 		char *input = readline("$> ");
// 		int parts_num = find_parts_num(input);
// 		infiles_heredocs_num = find_infiles_heredocs_num(input, parts_num);
// 		free (input);
// 		int i = -1;
// 		while (++i < (parts_num))
// 			printf("part %d: %d\n", i, infiles_heredocs_num[i]);
// 		free (infiles_heredocs_num);
// 	}
// }