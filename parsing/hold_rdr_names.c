/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hold_rdr_names.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:46:19 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/26 21:22:43 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static void	hold_rdr_1(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qtrg)
	{
		var->qchr = str[var->i++];
		var->qtrg = TRUE;
	}
	else if ((str[var->i] == var->qchr) && var->qtrg)
	{
		if (str[++var->i] == ' ' && var->rtrg)
		{
			var->rnms[var->j][var->k][++var->l] = '\0';
			var->rtrg = FALSE;
		}
		var->qchr = '\0';
		var->qtrg = FALSE;
	}
	if (str[var->i] == '|' && !var->qtrg && !var->rtrg \
	&& var->j < var->parts_num)
	{
		var->rnms[var->j][++var->k] = NULL;
		var->k = -1;
		var->j++;
	}
}

static void	hold_rdr_2(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qtrg)
	{
		var->qchr = str[var->i++];
		var->qtrg = TRUE;
	}
	else if ((str[var->i] == var->qchr) && var->qtrg)
	{
		if (str[++var->i] == ' ' && var->rtrg)
		{
			var->rnms[var->j][var->k][++var->l] = '\0';
			var->rtrg = FALSE;
		}
		var->qchr = '\0';
		var->qtrg = FALSE;
	}
	if (str[var->i] == '|' && !var->qtrg && !var->rtrg \
	&& var->j < var->parts_num)
	{
		var->rnms[var->j][++var->k] = NULL;
		var->k = -1;
		var->j++;
	}
}

static t_bool	hold_rdr_3(t_var *var, char *str)
{
	if (var->i < var->len - 1 && (str[var->i] == '<' && str[var->i + 1] != '<' \
	&& (var->i == 0 || str[var->i - 1] != '<') && (var->i == 0 \
	|| str[var->i - 1] != '>')) && !var->rtrg && !var->qtrg \
	&& var->k < var->rnum[var->j])
	{
		var->l = -1;
		var->rtrg = TRUE;
		var->k++;
		var->i++;
		if (str[var->i] == ' ')
			var->i++;
	}
	else if (var->i < var->len - 1 && (str[var->i] == '<' \
	&& str[var->i + 1] == '<') && !var->rtrg && !var->qtrg \
	&& var->k < var->rnum[var->j])
	{
		var->l = -1;
		var->rtrg = TRUE;
		var->k++;
		var->i += 2;
		if (str[var->i] == ' ')
			var->i++;
	}
	return (var->rtrg);
}

t_bool	hold_rdr_cont(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qtrg)
	{
		var->qchr = str[var->i];
		var->qtrg = TRUE;
		return (TRUE);
	}
	else if ((str[var->i] == var->qchr) && var->qtrg)
	{
		var->qchr = '\0';
		var->qtrg = FALSE;
		return (TRUE);
	}
	if (((str[var->i] != '<' && str[var->i] != '>' && str[var->i] != ' ' \
	&& str[var->i] != '|' && str[var->i] != '\'' && str[var->i] != '"' \
	&& str[var->i] != '\0') && !var->qtrg && var->rtrg))
	{
		var->rnms[var->j][var->k][++(var->l)] = str[var->i];
		if (str[var->i + 1] == '<' || str[var->i + 1] == '>' \
		|| str[var->i + 1] == ' ' || str[var->i + 1] == '|')
		{
			var->rnms[var->j][var->k][++var->l] = '\0';
			var->rtrg = FALSE;
		}
	}
	return (FALSE);
}

char	***hold_rdr_names(char *str, char rdr, t_parse *data)
{
	t_var	var;

	if (rdr == '<' && !data->tot_inredir)
		return (NULL);
	else if (rdr == '>' && !data->tot_outredir)
		return (NULL);
	init_rdr_vars(&var, str, rdr);
	if (rdr == '<' && data->tot_inredir)
		var.rnum = data->in_rdr_num;
	else if (rdr == '>' && data->tot_outredir)
		var.rnum = data->out_rdr_num;
	var.rcn = find_rdr_chars(str, rdr, data);
	var.rnms = malloc_rdr_names(var.parts_num, var.rnum, var.rcn);
	while (++var.i < var.len && str[var.i])
	{
		hold_rdr_1(&var, str);
		hold_rdr_2(&var, str);
		if (!hold_rdr_3(&var, str))
		{	
			if ((str[var.i] == '<' || str[var.i] == '>' \
			|| str[var.i] == ' ' || str[var.i] == '|' \
			|| str[var.i] != var.qchr) && var.qtrg && var.rtrg)
				var.rnms[var.j][var.k][++var.l] = str[var.i];
		}
		if (hold_rdr_cont(&var, str))
			continue ;
	}
	if (var.rnms[var.j])
		var.rnms[++var.j] = NULL;
	return (var.rnms);
}
