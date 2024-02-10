/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hold_rdr_names.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:46:19 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/10 10:53:18 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static void	hold_rdr_1(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qchr = str[var->i++];
		var->qutrg = TRUE;
	}
	else if ((str[var->i] == var->qchr) && var->qutrg)
	{
		if (str[++var->i] == ' ' && var->rdrtrg)
		{
			var->rnms[var->j][var->k][++var->l] = '\0';
			var->rdrtrg = FALSE;
		}
		var->qchr = '\0';
		var->qutrg = FALSE;
	}
	if (str[var->i] == '|' && !var->qutrg && !var->rdrtrg \
	&& var->j < var->parts_num)
	{
		var->rnms[var->j][++var->k] = NULL;
		var->k = -1;
		var->j++;
	}
}

static t_bool	hold_rdr_2(t_var *var, char *str, char rdr)
{
	if (var->i < var->len - 1 && (str[var->i] == rdr && str[var->i + 1] != rdr \
	&& (var->i == 0 || str[var->i - 1] != rdr)) && !var->rdrtrg && !var->qutrg \
	&& var->k < var->rnum[var->j])
	{
		var->l = -1;
		var->rdrtrg = TRUE;
		var->k++;
		var->i++;
		if (str[var->i] == ' ')
			var->i++;
	}
	else if (var->i < var->len - 1 && (str[var->i] == rdr \
	&& str[var->i + 1] == rdr) && !var->rdrtrg && !var->qutrg \
	&& var->k < var->rnum[var->j])
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
		var->qchr = str[var->i];
		var->qutrg = TRUE;
		return (TRUE);
	}
	else if ((str[var->i] == var->qchr) && var->qutrg)
	{
		var->qchr = '\0';
		var->qutrg = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

static void	copy_and_null(t_var *var, char *str)
{
	if (((str[var->i] != '<' && str[var->i] != '>' && str[var->i] != ' ' \
	&& str[var->i] != '|' && str[var->i] != '\'' && str[var->i] != '"' \
	&& str[var->i] != '\0') && var->rdrtrg))
	{
		var->rnms[var->j][var->k][++var->l] = str[var->i];
		if (str[var->i + 1] == '<' || str[var->i + 1] == '>' \
		|| str[var->i + 1] == ' ' || str[var->i + 1] == '|' \
		|| str[var->i + 1] == '\0')
		{
			var->rnms[var->j][var->k][++var->l] = '\0';
			var->rdrtrg = FALSE;
		}
	}
}

char	***hold_rdr_names(char *str, char rdr, t_parse *data)
{
	t_var	var;

	if (init_rdr_vars(&var, data, str, rdr))
		return (NULL);
	var.rcn = find_rdr_chars(str, rdr, data);
	var.rnms = malloc_rdr_names(var.parts_num, var.rnum, var.rcn);
	ft_free_intarr(var.rcn, var.parts_num);
	while (++var.i < var.len && str[var.i])
	{
		hold_rdr_1(&var, str);
		if (!hold_rdr_2(&var, str, rdr))
		{
			if ((str[var.i] == '<' || str[var.i] == '>' \
			|| str[var.i] == ' ' || str[var.i] == '|' \
			|| str[var.i] != var.qchr) && var.qutrg && var.rdrtrg)
				var.rnms[var.j][var.k][++var.l] = str[var.i];
		}
		if (hold_rdr_cont(&var, str))
			continue ;
		copy_and_null(&var, str);
	}
	if (var.rnms[var.j])
		var.rnms[++var.j] = NULL;
	return (var.rnms);
}
