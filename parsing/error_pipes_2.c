/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:52:54 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/06 05:31:30 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static t_bool check_end_pipe(char *str)
{
	int		i;
	t_bool	trigger;
	int		len;
	
	len = ft_strlen(str);
	trigger = FALSE;
	i = -1;
	while (++i < len)
	{
		if (str[i] != ' ' && str[i] != '\t')
			trigger = TRUE;
		else if ((str[i + 1] == '\0' || str[i + 1] == '|') && !trigger)
			return (TRUE);
	}
	return (FALSE);
}

static t_bool check_redir_end(char *str)
{
	int	i;
	t_bool	trigger;
	int		len;
	
	len = ft_strlen(str);
	trigger = FALSE;
	i = -1;
	if (str[0] == '<' || str[0] == '>')
		i = 0;
	while (++i < len)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '<' && str[i] != '>' && str[i] != '|')
			trigger = TRUE;
		else if ((str[i] == '\0' || str[i] == '<'\
			|| str[i] == '>' || str[i] == '|') && !trigger)
			return (TRUE);
	}
	return (FALSE);
}

// error: double pipe or more (next to each other), if (< < or > > or >>> or <<<) or more
t_bool	check_pipe_red_2(char *str)
{
	int		i;
	t_bool	quo_trigger;
	int		len;
	
	len = ft_strlen(str);
	quo_trigger = FALSE;
	i = -1;
	while (++i < len)
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!quo_trigger)
			{
				quo_trigger = TRUE;
				jump_over_quote(str, &i, len);
			}
			else 
				quo_trigger = FALSE;
		}
		if ((str[i] == '<' && str[i + 1] == '>') || (str[i] == '>' && str[i + 1] == '<'))
			return (TRUE);
		else if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<') \
				|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
			return (TRUE);
		else if ((str[i] == '<' || str[i] == '>'))
		{
			if (str[i + 1] == '|' || str[i + 1] == '\0' || check_redir_end(str + (i + 1)))
				return (TRUE);
		}
		else if (str[i] == '|')
		{
			if (str[i + 1] == '|' || str[i + 1] == '\0' || check_end_pipe(str + (i + 1)))
				return (TRUE);
		}
	}
	return (FALSE);
}
