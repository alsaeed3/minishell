/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outputs_chars_num.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 22:12:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/13 17:58:20 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	**find_oc_num(char *cmd_line)
{
	int	i;
	int j;
	int	k;
	int	len;
	int parts_num;
	int *outputs_num;
	t_bool	redi_trigger;
	t_bool	quo_trigger;
	char	quo_char;
	int	char_num;
	int **ocm;

	parts_num = find_parts_num(cmd_line);
	outputs_num = find_outfiles_appends_num(cmd_line);
	ocm = ft_calloc(parts_num, sizeof(int *));
	len = ft_strlen(cmd_line);
	i = -1;
	while (++i < parts_num)
		ocm[i] = ft_calloc(outputs_num[i], sizeof(int));
	redi_trigger = FALSE;
	quo_trigger = FALSE;
	i = -1;
	k = -1;
	j = 0;
	while (++i < len && cmd_line[i])
	{
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i++];
			quo_trigger = TRUE;
		}
		else if((cmd_line[i] == quo_char) && quo_trigger)
		{
			if (cmd_line[++i] == ' ' && redi_trigger)
				redi_trigger = FALSE;
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == '|' && !quo_trigger && !redi_trigger && j < parts_num)
		{
			j++;
			k = -1;
		}
		if (i < len - 1 && (cmd_line[i] == '>' && cmd_line[i + 1] != '>' && (i == 0 || cmd_line[i - 1] != '>') && (i == 0 || cmd_line[i - 1] != '>')) && !redi_trigger && !quo_trigger && k < outputs_num[j])
		{
			char_num = 0;
			redi_trigger = TRUE;
			k++;
			i++;
			if (cmd_line[i] == ' ')
				i++;
		}
		else if (i < len - 1 && (cmd_line[i] == '>' && cmd_line[i + 1] == '>') && !redi_trigger && !quo_trigger && k < outputs_num[j])
		{
			char_num = 0;
			redi_trigger = TRUE;
			k++;
			i += 2;
			if (cmd_line[i] == ' ')
				i++;
		}
		else if ((cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == ' ' || cmd_line[i] == '|' || cmd_line[i] != quo_char) && quo_trigger && redi_trigger)
			ocm[j][k] = ++char_num;
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			continue ;
		}
		else if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			continue ;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"' && cmd_line[i] != '\0') && !quo_trigger && redi_trigger))
		{
			ocm[j][k] = ++char_num;
			if (cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>' || cmd_line[i + 1] == ' ' || cmd_line[i + 1] == '|')
				redi_trigger = FALSE;
		}
	}
	return (ocm);
}

// int main()
// {
// 	while (1)
// 	{
// 		char *cmd_line = readline("$> ");
// 		int parts_num = find_parts_num(cmd_line);
// 		int *oan = find_outfiles_appends_num(cmd_line, parts_num);
// 		int **oc = find_oc_num(cmd_line, parts_num, oan);
// 		free(cmd_line);
// 		int j;
// 		int i = -1;
// 		while (++i < parts_num)
// 		{
// 			j = -1;
// 			while (++j < oan[i])
// 				printf("part: %d, redir: %d, chars: %d\n", i, j, oc[i][j]);
// 		}
// 		i = -1;
// 		while (++i < parts_num)
// 			free(oc[i]);
// 		free(oc);
// 		free(oan);
// 	}
//     return 0;
// }
