/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocing_in_redir_file_names.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:46:19 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/25 13:35:35 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// t_bool is_in_redir(char *cmd_line)
// {
// 	int	i;
// 	t_bool	quo_trigger;
// 	char	quo_char;
// }

char	***hold_rdr_names(char *str, char rdr)
{
	t_var	var;

	init_vars(&var, str, 2, rdr);
	while (++var.i < var.len && str[var.i])
	{
		if((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.quchr = str[var.i++];
			var.qutrg = TRUE;
		}
		else if((str[var.i] == var.quchr) && var.qutrg)
		{
			if (str[++var.i] == ' ' && var.rdrtrg)
			{
				var.rdrnms[var.j][var.k][++var.l] = '\0';
				var.rdrtrg = FALSE;
			}
			var.quchr = '\0';
			var.qutrg = FALSE;
		}
		if (str[var.i] == '|' && !var.qutrg && !var.rdrtrg && var.j < var.parts_num)
		{
			var.rdrnms[var.j][++var.k] = NULL;
			var.k = -1;
			var.j++;
		}
		if (var.i < var.len - 1 && (str[var.i] == '<' && str[var.i + 1] != '<' && (var.i == 0 || str[var.i - 1] != '<') && (var.i == 0 || str[var.i - 1] != '>')) && !var.rdrtrg && !var.qutrg && var.k < var.rdrnum[var.j])
		{
			var.l = -1;
			var.rdrtrg = TRUE;
			var.k++;
			var.i++;
			if (str[var.i] == ' ')
				var.i++;
		}
		else if (var.i < var.len - 1 && (str[var.i] == '<' && str[var.i + 1] == '<') && !var.rdrtrg && !var.qutrg && var.k < var.rdrnum[var.j])
		{
			var.l = -1;
			var.rdrtrg = TRUE;
			var.k++;
			var.i += 2;
			if (str[var.i] == ' ')
				var.i++;
		}
		else if ((str[var.i] == '<' || str[var.i] == '>' || str[var.i] == ' ' || str[var.i] == '|' || str[var.i] != var.quchr) && var.qutrg && var.rdrtrg)
			var.rdrnms[var.j][var.k][++var.l] = str[var.i];
		if ((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.quchr = str[var.i];
			var.qutrg = TRUE;
			continue;
		}
		else if ((str[var.i] == var.quchr) && var.qutrg)
		{
			var.quchr = '\0';
			var.qutrg = FALSE;
			continue ;
		}
		if (((str[var.i] != '<' && str[var.i] != '>' && str[var.i] != ' ' && str[var.i] != '|' && str[var.i] != '\'' && str[var.i] != '"' && str[var.i] != '\0') && !var.qutrg && var.rdrtrg))
		{
			var.rdrnms[var.j][var.k][++var.l] = str[var.i];
			if (str[var.i + 1] == '<' || str[var.i + 1] == '>' || str[var.i + 1] == ' ' || str[var.i + 1] == '|')
			{
				var.rdrnms[var.j][var.k][++var.l] = '\0';
				var.rdrtrg = FALSE;
			}
		}
	}
	if(var.rdrnms[var.j])
		var.rdrnms[++var.j] = NULL;
	return (var.rdrnms);
}
