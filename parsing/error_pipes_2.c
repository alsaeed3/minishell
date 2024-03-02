/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:52:54 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/12 16:18:15 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static t_bool check_end_pipe(char *cmd_line)
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:52:54 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/15 14:35:08 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static t_bool	check_end_pipe(char *str)
>>>>>>> main
{
	int		i;
	t_bool	trigger;
	int		len;
<<<<<<< HEAD
	
	len = ft_strlen(cmd_line);
=======

	len = ft_strlen(str);
>>>>>>> main
	trigger = FALSE;
	i = -1;
	while (++i < len)
	{
<<<<<<< HEAD
		if (cmd_line[i] != ' ' && cmd_line[i] != '\t')
			trigger = TRUE;
		else if ((cmd_line[i + 1] == '\0' || cmd_line[i + 1] == '|') && !trigger)
=======
		if (str[i] != ' ' && str[i] != '\t')
			trigger = TRUE;
		else if ((str[i + 1] == '\0' \
		|| str[i + 1] == '|') && !trigger)
>>>>>>> main
			return (TRUE);
	}
	return (FALSE);
}

<<<<<<< HEAD
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
=======
static t_bool	check_redir_end(char *str)
{
	int		i;
	t_bool	trigger;
	int		len;

	len = ft_strlen(str);
	trigger = FALSE;
	i = -1;
	if (str[0] == '<' || str[0] == '>')
		i = 0;
	while (++i < len)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '<' \
		&& str[i] != '>' && str[i] != '|')
			trigger = TRUE;
		else if ((str[i] == '\0' || str[i] == '<'\
			|| str[i] == '>' || str[i] == '|') && !trigger)
>>>>>>> main
			return (TRUE);
	}
	return (FALSE);
}

<<<<<<< HEAD
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
=======
static void	init_var(t_var *var, char *str)
{
	var->len = ft_strlen(str);
	var->qutrg = FALSE;
	var->i = -1;
	var->qchr = '\0';
}

static t_bool	check_error(t_var var, char *str)
{
	if (((str[var.i] == '<' && str[var.i + 1] == '>') \
	|| (str[var.i] == '>' && str[var.i + 1] == '<')) && !var.qutrg)
		return (TRUE);
	else if (((str[var.i] == '<' && str[var.i + 1] == '<' \
	&& str[var.i + 2] == '<') || (str[var.i] == '>' \
	&& str[var.i + 1] == '>' && str[var.i + 2] == '>')) && !var.qutrg)
		return (TRUE);
	else if ((str[var.i] == '<' || str[var.i] == '>') && !var.qutrg)
	{
		if (str[var.i + 1] == '|' || str[var.i + 1] == '\0' \
		|| check_redir_end(str + (var.i + 1)))
			return (TRUE);
	}
	else if (str[var.i] == '|' && !var.qutrg)
	{
		if (str[var.i + 1] == '|' || str[var.i + 1] == '\0' \
		|| check_end_pipe(str + (var.i + 1)))
			return (TRUE);
	}
	return (FALSE);
}

// error: double pipe or more 
// (next to each other), if (< < or > > or >>> or <<<) or more
t_bool	check_pipe_red_2(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_var(&var, str);
	while (++var.i < var.len)
	{
		if ((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.qchr = str[var.i];
			var.qutrg = TRUE;
		}
		else if (str[var.i] == var.qchr && var.qutrg)
		{
			var.qchr = '\0';
			var.qutrg = FALSE;
		}
		if (!var.qutrg && check_error(var, str))
			return (TRUE);
>>>>>>> main
	}
	return (FALSE);
}
