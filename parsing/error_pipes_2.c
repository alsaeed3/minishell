/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:52:54 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/12 16:18:15 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static t_bool check_end_pipe(char *cmd_line)
{
	int		i;
	t_bool	trigger;
	int		len;
	
	len = ft_strlen(cmd_line);
	trigger = FALSE;
	i = -1;
	while (++i < len)
	{
		if (cmd_line[i] != ' ' && cmd_line[i] != '\t')
			trigger = TRUE;
		else if ((cmd_line[i + 1] == '\0' || cmd_line[i + 1] == '|') && !trigger)
			return (TRUE);
	}
	return (FALSE);
}

static t_bool check_redir_end(char *cmd_line)
{
	int	i;
	t_bool	trigger;
	int		len;
	
	len = ft_strlen(cmd_line);
	trigger = FALSE;
	i = -1;
	if (cmd_line[0] == '<' || cmd_line[0] == '>')
		i = 0;
	while (++i < len)
	{
		if (cmd_line[i] != ' ' && cmd_line[i] != '\t' && cmd_line[i] != '<' && cmd_line[i] != '>' && cmd_line[i] != '|')
			trigger = TRUE;
		else if ((cmd_line[i] == '\0' || cmd_line[i] == '<'\
			|| cmd_line[i] == '>' || cmd_line[i] == '|') && !trigger)
			return (TRUE);
	}
	return (FALSE);
}

// error: double pipe or more (next to each other), if (< < or > > or >>> or <<<) or more
t_bool	check_pipe_red_2(char *cmd_line)
{
	int		i;
	t_bool	quo_trigger;
	char	quo_char;
	int		len;
	
	len = ft_strlen(cmd_line);
	quo_trigger = FALSE;
	i = -1;
	quo_char = '\0';
	while (++i < len)
	{
		if ((cmd_line[i] == '\'' || cmd_line[i] == '"'))
		{
			if (!quo_trigger)
			{
				quo_char = cmd_line[i];
				quo_trigger = TRUE;
				jump_over_quote(cmd_line, &i, len);
			}
			else if (cmd_line[i] == quo_char && quo_trigger)
			{
				quo_char = '\0';
				quo_trigger = FALSE;
			}
		}
		if (((cmd_line[i] == '<' && cmd_line[i + 1] == '>') || (cmd_line[i] == '>' && cmd_line[i + 1] == '<')) && !quo_trigger)
			return (TRUE);
		else if (((cmd_line[i] == '<' && cmd_line[i + 1] == '<' && cmd_line[i + 2] == '<') \
				|| (cmd_line[i] == '>' && cmd_line[i + 1] == '>' && cmd_line[i + 2] == '>')) && !quo_trigger)
			return (TRUE);
		else if ((cmd_line[i] == '<' || cmd_line[i] == '>') && !quo_trigger)
		{
			if (cmd_line[i + 1] == '|' || cmd_line[i + 1] == '\0' || check_redir_end(cmd_line + (i + 1)))
				return (TRUE);
		}
		else if (cmd_line[i] == '|' && !quo_trigger)
		{
			if (cmd_line[i + 1] == '|' || cmd_line[i + 1] == '\0' || check_end_pipe(cmd_line + (i + 1)))
				return (TRUE);
		}
	}
	return (FALSE);
}
