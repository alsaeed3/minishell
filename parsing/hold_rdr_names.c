/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hold_rdr_names.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:46:19 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/25 21:19:41 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static void	hold_rdr_1(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->quchr = str[var->i++];
		var->qutrg = TRUE;
	}
	else if ((str[var->i] == var->quchr) && var->qutrg)
	{
		if (str[++var->i] == ' ' && var->rdrtrg)
		{
			var->rdrnms[var->j][var->k][++var->l] = '\0';
			var->rdrtrg = FALSE;
		}
		var->quchr = '\0';
		var->qutrg = FALSE;
	}
	if (str[var->i] == '|' && !var->qutrg && !var->rdrtrg \
	&& var->j < var->parts_num)
	{
		var->rdrnms[var->j][++var->k] = NULL;
		var->k = -1;
		var->j++;
	}
}

static void	hold_rdr_2(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->quchr = str[var->i++];
		var->qutrg = TRUE;
	}
	else if ((str[var->i] == var->quchr) && var->qutrg)
	{
		if (str[++var->i] == ' ' && var->rdrtrg)
		{
			var->rdrnms[var->j][var->k][++var->l] = '\0';
			var->rdrtrg = FALSE;
		}
		var->quchr = '\0';
		var->qutrg = FALSE;
	}
	if (str[var->i] == '|' && !var->qutrg && !var->rdrtrg \
	&& var->j < var->parts_num)
	{
		var->rdrnms[var->j][++var->k] = NULL;
		var->k = -1;
		var->j++;
	}
}

static t_bool	hold_rdr_3(t_var *var, char *str)
{
	if (var->i < var->len - 1 && (str[var->i] == '<' && str[var->i + 1] != '<' \
	&& (var->i == 0 || str[var->i - 1] != '<') && (var->i == 0 \
	|| str[var->i - 1] != '>')) && !var->rdrtrg && !var->qutrg \
	&& var->k < var->rdrnum[var->j])
	{
		var->l = -1;
		var->rdrtrg = TRUE;
		var->k++;
		var->i++;
		if (str[var->i] == ' ')
			var->i++;
	}
	else if (var->i < var->len - 1 && (str[var->i] == '<' \
	&& str[var->i + 1] == '<') && !var->rdrtrg && !var->qutrg \
	&& var->k < var->rdrnum[var->j])
	{
		var->l = -1;
		var->rdrtrg = TRUE;
		var->k++;
		var->i += 2;
		if (str[var->i] == ' ')
			var->i++;
	}
	return (var->rdrtrg);
}

t_bool	hold_rdr_cont(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->quchr = str[var->i];
		var->qutrg = TRUE;
		return (TRUE);
	}
	else if ((str[var->i] == var->quchr) && var->qutrg)
	{
		var->quchr = '\0';
		var->qutrg = FALSE;
		return (TRUE);
	}
	if (((str[var->i] != '<' && str[var->i] != '>' && str[var->i] != ' ' \
	&& str[var->i] != '|' && str[var->i] != '\'' && str[var->i] != '"' \
	&& str[var->i] != '\0') && !var->qutrg && var->rdrtrg))
	{
		var->rdrnms[var->j][var->k][++var->l] = str[var->i];
		if (str[var->i + 1] == '<' || str[var->i + 1] == '>' \
		|| str[var->i + 1] == ' ' || str[var->i + 1] == '|')
		{
			var->rdrnms[var->j][var->k][++var->l] = '\0';
			var->rdrtrg = FALSE;
		}
	}
	return (FALSE);
}

char	***hold_rdr_names(char *str, char rdr)
{
	printf("hold_rdr_names %c\n", rdr);
	t_var	var;

	init_rdr_vars(&var, str, 3, rdr);
	var.rcn = find_rdr_chars(str, rdr);
	var.rdrnms = malloc_rdr_names(var.parts_num, var.rdrnum, var.rcn);
	while (++var.i < var.len && str[var.i])
	{
		hold_rdr_1(&var, str);
		hold_rdr_2(&var, str);
		if (!hold_rdr_3(&var, str))
		{	
			if ((str[var.i] == '<' || str[var.i] == '>' \
			|| str[var.i] == ' ' || str[var.i] == '|' \
			|| str[var.i] != var.quchr) && var.qutrg && var.rdrtrg)
				var.rdrnms[var.j][var.k][++var.l] = str[var.i];
		}
		if (hold_rdr_cont(&var, str))
			continue ;
	}
	if (var.rdrnms[var.j])
		var.rdrnms[++var.j] = NULL;
	return (var.rdrnms);
}
