/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocing_out_redir_file_names.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:44:49 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/05 00:48:37 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	***hold_output_file_names(char *cmd_line, int parts_num, int *outputs_num, int ** oc_num)
{
	int	i;
	int j;
	int	k;
	int	l;
	int	len;
	bool	redi_trigger;
	bool	quo_trigger;
	char	quo_char;
	char	***redir_names;

	redir_names = malloc_outputs(parts_num, outputs_num, oc_num);
	if (!redir_names)
		return (NULL);
	redi_trigger = false;
	quo_trigger = false;
	i = -1;
	k = 0;
	j = 0;
	l = 0;
	len = (int)ft_strlen(cmd_line);
	while (++i < len)
	{
		if (cmd_line[i] == '|' && !quo_trigger && !redi_trigger)
		{
			k = 0;
			j++;
		}
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger && redi_trigger)
		{
			quo_char = cmd_line[i++];
			quo_trigger = true;
		}
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger && !redi_trigger)
			jump_over_quote(cmd_line, &i, len);
		else if((cmd_line[i] == quo_char) && redi_trigger && quo_char)
			quo_trigger = false;
		else if (((cmd_line[i] == '"' || cmd_line[i] == '\'' || cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == '|')) && redi_trigger && quo_trigger)
			redir_names[j][k][l++] = cmd_line[i];;
		if ((cmd_line[i] == '>' && cmd_line[i + 1] != '>' && cmd_line[i - 1] != '>') && !redi_trigger && !quo_trigger)
		{
			l = 0;
			redi_trigger = true;
			if (cmd_line[i + 1] == ' ')
				i++;
		}
		if ((cmd_line[i] == '>' && cmd_line[i + 1] == '>') && !redi_trigger && !quo_trigger)
		{
			l = 0;
			redi_trigger = true;
			i++;
			if (cmd_line[i + 1] == ' ')
				i++;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"') && redi_trigger))
			redir_names[j][k][l++] = cmd_line[i];;
		if (cmd_line[i] == ' ' && redi_trigger && quo_trigger)
			redir_names[j][k][l++] = cmd_line[i];
		if ((cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>' || cmd_line[i + 1] == ' ' || cmd_line[i + 1] == '|' || cmd_line[i + 1] == '\0') && redi_trigger && !quo_trigger)
		{
			redir_names[j][k++][l] = '\0';
			redi_trigger = false;
		}
	}
	return (redir_names);
}