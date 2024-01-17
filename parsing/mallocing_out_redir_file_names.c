/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocing_out_redir_file_names.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:44:49 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/13 18:25:31 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	***hold_output_file_names(char *cmd_line)
{
	int	i;
	int j;
	int	k;
	int	l;
	int	len;
	int parts_num;
	int *outputs_num;
	int **ocm;
	t_bool	redi_trigger;
	t_bool	quo_trigger;
	char	quo_char;
	char	***redir_names;

	parts_num = find_parts_num(cmd_line);
	outputs_num = find_outfiles_appends_num(cmd_line);
	ocm = find_oc_num(cmd_line);
	redir_names = malloc_file_names(parts_num, outputs_num, ocm);
	if (!redir_names)
		return (NULL);
	redi_trigger = FALSE;
	quo_trigger = FALSE;
	quo_char = '\0';
	i = -1;
	k = -1;
	j = 0;
	l = -1;
	len = (int)ft_strlen(cmd_line);
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
			{
				redir_names[j][k][++l] = '\0';
				redi_trigger = FALSE;
			}
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (cmd_line[i] == '|' && !quo_trigger && !redi_trigger && j < parts_num)
		{
			redir_names[j][++k] = NULL;
			k = -1;
			j++;
		}
		if (i < len - 1 && (cmd_line[i] == '>' && cmd_line[i + 1] != '>' && (i == 0 || cmd_line[i - 1] != '>') && (i == 0 || cmd_line[i - 1] != '<')) && !redi_trigger && !quo_trigger && k < outputs_num[j])
		{
			l = -1;
			redi_trigger = TRUE;
			k++;
			i++;
			if (cmd_line[i] == ' ')
				i++;
		}
		else if (i < len - 1 && (cmd_line[i] == '>' && cmd_line[i + 1] == '>') && !redi_trigger && !quo_trigger && k < outputs_num[j])
		{
			l = -1;
			redi_trigger = TRUE;
			k++;
			i += 2;
			if (cmd_line[i] == ' ')
				i++;
		}
		else if ((cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == ' ' || cmd_line[i] == '|' || cmd_line[i] != quo_char) && quo_trigger && redi_trigger)
			redir_names[j][k][++l] = cmd_line[i];
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			continue;
		}
		else if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			continue ;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"' && cmd_line[i] != '\0') && !quo_trigger && redi_trigger))
		{
			redir_names[j][k][++l] = cmd_line[i];
			if (cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>' || cmd_line[i + 1] == ' ' || cmd_line[i + 1] == '|')
			{
				redir_names[j][k][++l] = '\0';
				redi_trigger = FALSE;
			}
		}
	}
	if(redir_names[j])
		redir_names[++j] = NULL;
	return (redir_names);
}
