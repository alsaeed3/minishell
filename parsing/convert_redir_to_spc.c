/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir_to_spc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:03:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/06 05:31:30 by alsaeed          ###   ########.fr       */
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
	t_bool	redi_trigger;
	t_bool	quo_trigger;
	char	quo_char;

	redi_trigger = FALSE;
	quo_trigger = FALSE;
	len = ft_strlen(cmd_line);
	no_redir = ft_calloc((len + 1), sizeof(char));
	i = -1;
	while (++i < len)
	{
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger && redi_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
		}
		else if((cmd_line[i] == quo_char) && redi_trigger && quo_char)
			quo_trigger = FALSE;
		else if ((cmd_line[i] == '<' && cmd_line[i + 1] != '<' && cmd_line[i - 1] != '<') && !redi_trigger && !quo_trigger)
			redi_trigger = TRUE;
		else if ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') && !redi_trigger && !quo_trigger)
			redi_trigger = TRUE;
		if ((cmd_line[i + 1] == '<' || cmd_line[i + 1] == '>' || cmd_line[i + 1] == ' ' || cmd_line[i + 1] == '|' || cmd_line[i + 1] == '\0') && redi_trigger && !quo_trigger)
			redi_trigger = FALSE;
		if (redi_trigger)
			no_redir[i] = cmd_line[i];
		else if (redi_trigger)
			no_redir[i] = ' ';
	}
	no_redir[i] = '\0';
	return (no_redir);
}
