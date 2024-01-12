/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir_to_spc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:03:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/12 12:10:15 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
/* In this function I'm converting all the redirections symbols with their */
/* file names to spaces in the command line after saving all the file names */
/* with their tokens */

int	count_size_without_redir(char *cmd_line)
{
	char *no_redir;
	int	len;
	int i;
	int j;
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
	j = 0;
	while (++i < len && cmd_line[i])
	{
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			j++;
		}
		else if((cmd_line[i] == quo_char) && quo_char)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			j++;
		}
		if (i < len - 1 && ((cmd_line[i] == '<' && cmd_line[i + 1] != '<' && (i == 0 || cmd_line[i - 1] != '<')) || (cmd_line[i] == '>' && cmd_line[i + 1] != '>' && (i == 0 || cmd_line[i - 1] != '>'))) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			j++;
			if (cmd_line[i] == ' ')
				j++;
		}
		else if (i < len - 1 && ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') || (cmd_line[i] == '>' && cmd_line[i + 1] == '>')) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			j += 2;
			if (cmd_line[i] == ' ')
				j++;
		}
		if (cmd_line[i] == ' ' && redi_trigger && !quo_trigger)
		{
			j++;
			redi_trigger = FALSE;
		}
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			j++;
			continue;
		}
		if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			j++;
			continue;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"') && !quo_trigger && redi_trigger))
		{
			j++;
			continue ;
		}
		j++;
	}
	return (j);
}

char *conv_redir2spcs(char *cmd_line)
{
	char *no_redir;
	int	len;
	int	size_without_redir;
	int i;
	int j;
	t_bool	redi_trigger;
	t_bool	quo_trigger;
	char	quo_char;

	redi_trigger = FALSE;
	quo_trigger = FALSE;
	size_without_redir = count_size_without_redir(cmd_line);
	no_redir = ft_calloc((size_without_redir + 1), sizeof(char));
	if (!no_redir)
		exit (1);
	len = ft_strlen(cmd_line);
	i = -1;
	j = 0;
	while (++i < len && cmd_line[i])
	{
		if((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			if (redi_trigger)
				no_redir[j++] = ' ';
			else
				no_redir[j++] = cmd_line[i++];
		}
		else if((cmd_line[i] == quo_char) && quo_char)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			if (redi_trigger)
				no_redir[j++] = ' ';
			else
				no_redir[j++] = cmd_line[i++];
		}
		if (i < len - 1 && ((cmd_line[i] == '<' && cmd_line[i + 1] != '<' && (i == 0 || cmd_line[i - 1] != '<')) || (cmd_line[i] == '>' && cmd_line[i + 1] != '>' && (i == 0 || cmd_line[i - 1] != '>'))) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			no_redir[j++] = ' ';
			if (cmd_line[i] == ' ')
				no_redir[j++] = ' ';
		}
		else if (i < len - 1 && ((cmd_line[i] == '<' && cmd_line[i + 1] == '<') || (cmd_line[i] == '>' && cmd_line[i + 1] == '>')) && !redi_trigger && !quo_trigger)
		{
			redi_trigger = TRUE;
			no_redir[j++] = ' ';
			no_redir[j++] = ' ';
			if (cmd_line[i] == ' ')
				no_redir[j++] = ' ';
		}
		if (cmd_line[i] == ' ' && redi_trigger && !quo_trigger)
		{
			no_redir[j++] = ' ';
			redi_trigger = FALSE;
		}
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"') && !quo_trigger)
		{
			quo_char = cmd_line[i];
			quo_trigger = TRUE;
			if (redi_trigger)
				no_redir[j++] = ' ';
			else
				no_redir[j++] = cmd_line[i];
			continue;
		}
		if ((cmd_line[i] == quo_char) && quo_trigger)
		{
			quo_char = '\0';
			quo_trigger = FALSE;
			if (redi_trigger)
				no_redir[j++] = ' ';
			else
				no_redir[j++] = cmd_line[i];
			continue;
		}
		if (((cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != ' ' && cmd_line[i] != '|' && cmd_line[i] != '\'' && cmd_line[i] != '"') && !quo_trigger && redi_trigger))
		{
			no_redir[j++] = ' ';
			continue ;
		}
		if (!redi_trigger)
			no_redir[j++] = cmd_line[i];
		else
			no_redir[j++] = ' ';
	}
	if (no_redir[j])
		no_redir[++j] = '\0';
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