/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir_to_spc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:03:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/05 01:30:04 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
/* In this function I'm converting all the redirections symbols with their */
/* file names to spaces in the command line after saving all the file names */
/* with their tokens */

char *conv_redir2spcs(char *cmd_line)
{
	char *no_redir;
	int	len;
	int i;
	bool	redi_trigger;
	bool	quo_trigger;
	char	quo_char;

	redi_trigger = false;
	quo_trigger = false;
	len = ft_strlen(cmd_line);
	no_redir = ft_calloc((len + 1), sizeof(char));
	i = -1;
	while (++i < len)
	{
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger && redi_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = true;
		}
		else if((cmd_line[i] == quo_char) && redi_trigger && quo_char)
			quo_trigger = false;
		else if ((cmd_line[i] == '<' && cmd_line[i + 1] != '<' && cmd_line[i - 1] != '<') && !redi_trigger && !quo_trigger)
			redi_trigger = true;
		else if ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') && !redi_trigger && !quo_trigger)
			redi_trigger = true;
		if ((cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>' || cmd_line[i + 1] == ' ' || cmd_line[i + 1] == '|' || cmd_line[i + 1] == '\0') && redi_trigger && !quo_trigger)
			redi_trigger = false;
		if (redi_trigger)
			no_redir[i] = cmd_line[i];
		else if (redi_trigger)
			no_redir[i] = ' ';
	}
	no_redir[i] = '\0';
	return (no_redir);
}
