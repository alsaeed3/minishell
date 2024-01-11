/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir_to_spc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:03:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/11 20:40:30 by alsaeed          ###   ########.fr       */
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
	if (!no_redir)
		exit (1);
	i = -1;
	while (++i < len && cmd_line[i])
	{
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger && redi_trigger)
		{
			quo_char = cmd_line[i];
			no_redir[i++] = ' ';
			quo_trigger = TRUE;
		}
		else if((cmd_line[i] == quo_char) && redi_trigger && quo_char)
		{
			no_redir[i++] = ' ';
			quo_char = '\0';
			quo_trigger = FALSE;
		}
		if (i < len - 2 && ((cmd_line[i] == '<' && cmd_line[i + 1] != '<' && (i == 0 || cmd_line[i - 1] != '<')) || (cmd_line[i] == '>' && cmd_line[i + 1] != '>' && (i == 0 || cmd_line[i - 1] != '>'))) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			no_redir[i++] = ' ';
			if (cmd_line[i] == ' ')
				no_redir[i++] = ' ';
		}
		else if (i < len - 3 && ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') || (cmd_line[i] == '>' && cmd_line[i + 1] == '>')) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			no_redir[i++] = ' ';
			no_redir[i++] = ' ';
			if (cmd_line[i] == ' ')
				no_redir[i++] = ' ';
		}
		if (cmd_line[i] == ' ' && redi_trigger && !quo_trigger)
		{
			no_redir[i++] = ' ';
			redi_trigger = FALSE;
		}
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && redi_trigger && !quo_trigger)
		{
			no_redir[i] = ' ';
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			continue;
		}
		if ((cmd_line[i] == quo_char) && redi_trigger && quo_trigger)
		{
			no_redir[i] = ' ';
			quo_char = '\0';
			quo_trigger = FALSE;
			continue;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"') && !quo_trigger && redi_trigger))
		{
			no_redir[i] = ' ';
			continue ;
		}
		if (!redi_trigger)
			no_redir[i] = cmd_line[i];
		else
			no_redir[i] = ' ';
	}
	if (no_redir[len - 1])
		no_redir[len] = '\0';
	return (no_redir);
}

// int main(void)
// {
// 	while (1)
// 	{
// 		char *read = readline("$> ");
// 		char *input = ft_strdup(read);
// 		// input = delete_excess_spcs(input);
// 		printf("%s\n", input);
// 		char *no_redir = conv_redir2spcs(input);
// 		free (input);
// 		printf("%s\n", no_redir);
// 		free (no_redir);
// 	}
// }