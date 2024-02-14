/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 20:52:54 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/14 16:36:19 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static t_bool	check_end_pipe(char *str)
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
		else if ((str[i + 1] == '\0' \
		|| str[i + 1] == '|') && !trigger)
			return (TRUE);
	}
	return (FALSE);
}

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
			return (TRUE);
	}
	return (FALSE);
}

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
		{
			ft_putchar_fd(str[var.i], 2);
			ft_putchar_fd('\n', 2);
			return (TRUE);
		}
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
	}
	return (FALSE);
}
