/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir_to_spc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:03:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/31 21:27:42 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
/* In this function I'm converting all the redirections symbols with their */
/* file names to spaces in the command line after saving all the file names */
/* with their tokens */

t_bool	check_quta(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qchr = str[var->i];
		var->qutrg = TRUE;
		var->j++;
	}
	else if ((str[var->i] == var->qchr) && var->qchr)
	{
		var->qchr = '\0';
		var->qutrg = FALSE;
		var->j++;
	}
	if (var->i < var->len - 1 && ((str[var->i] == '<' && str[var->i + 1] != '<' \
	&& (var->i == 0 || str[var->i - 1] != '<')) || (str[var->i] == '>' \
	&& str[var->i + 1] != '>' && (var->i == 0 || str[var->i - 1] != '>'))) \
	&& !var->rdrtrg && !var->qutrg)
	{
		var->rdrtrg = TRUE;
		var->j++;
		if (str[var->i] == ' ')
			var->j++;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	continue_count(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qchr = str[var->i];
		var->qutrg = TRUE;
		var->j++;
		return (TRUE);
	}
	if ((str[var->i] == var->qchr) && var->qutrg)
	{
		var->qchr = '\0';
		var->qutrg = FALSE;
		var->j++;
		return (TRUE);
	}
	if (((str[var->i] != '<' && str[var->i] != '>' && str[var->i] != ' ' \
	&& str[var->i] != '|' && str[var->i] != '\'' && str[var->i] != '"') \
	&& !var->qutrg && var->rdrtrg))
	{
		var->j++;
		return (TRUE);
	}
	return (FALSE);
}

void	init_nordr_vars(t_var *var, char *str, int mode)
{
	var->rdrtrg = FALSE;
	var->qutrg = FALSE;
	var->len = ft_strlen(str);
	var->i = -1;
	var->j = 0;
	if (mode == 1)
	{
		var->size = count_size_without_redir(str);
		var->nordr = ft_calloc((var->size + 1), sizeof(char));
	}
}

int	count_size_without_redir(char *str)
{
	t_var	var;

	init_nordr_vars(&var, str, 0);
	while (++var.i < var.len && str[var.i])
	{
		if (check_quta(&var, str))
			contin_check_qut(&var, str);
		if (str[var.i] == ' ' && (var.i == 0 || str[var.i - 1] != '<') \
		&& (var.i == 0 || str[var.i - 1] != '>') && var.rdrtrg && !var.qutrg)
		{
			var.j++;
			var.rdrtrg = FALSE;
		}
		if (continue_count(&var, str))
			continue ;
		var.j++;
	}
	return (var.j);
}

char	*conv_redir2spcs(char *str)
{
	t_var	var;

	init_nordr_vars(&var, str, 1);
	while (++var.i < var.len && str[var.i])
	{
		check_quot(&var, str);
		check_rdr(&var, str);
		if (continue_conv(&var, str))
			continue ;
		if (!var.rdrtrg)
			var.nordr[var.j++] = str[var.i];
		else if (str[var.i] != ' ' && var.rdrtrg)
			var.nordr[var.j++] = ' ';
	}
	if (var.nordr[var.j])
		var.nordr[++var.j] = '\0';
	free (str);
	str = NULL;
	return (var.nordr);
}
