/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rdr_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:57:18 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/06 20:43:04 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// to find each infile/heredoc file name characters and store them into
// a double pointer to use it later in mallocing

void	check_quout(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qchr = str[var->i++];
		var->qutrg = TRUE;
	}
	else if ((str[var->i] == var->qchr) && var->qutrg)
	{
		if (str[++var->i] == ' ' && var->rdrtrg)
			var->rdrtrg = FALSE;
		var->qchr = '\0';
		var->qutrg = FALSE;
	}
}

void	check_type(t_var *var, char *str, char rdr)
{
	if (var->i < var->len - 1 && (str[var->i] == rdr && str[var->i + 1] \
	!= rdr && (var->i == 0 || str[var->i - 1] != rdr)) \
	&& !var->rdrtrg && !var->qutrg && var->k < var->rnum[var->j])
	{
		var->cnum = 0;
		var->rdrtrg = TRUE;
		var->k++;
		var->i++;
		if (str[var->i] == ' ')
			var->i++;
	}
	else if (var->i < var->len - 1 && (str[var->i] == rdr && str[var->i + 1] \
	== rdr) && !var->rdrtrg && !var->qutrg && var->k < var->rnum[var->j])
	{
		var->cnum = 0;
		var->rdrtrg = TRUE;
		var->k++;
		var->i += 2;
		if (str[var->i] == ' ')
			var->i++;
	}
	else if ((str[var->i] == '<' || str[var->i] == '>' || str[var->i] == ' ' \
	|| str[var->i] == '|' || str[var->i] != var->qchr) && var->qutrg \
	&& var->rdrtrg)
		var->rcn[var->j][var->k] = ++var->cnum;
}

static t_bool	to_cont(t_var *var, char *str)
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

static void	count_rdr_chars(t_var *var, char *str)
{
	if (((str[var->i] != '<' && str[var->i] != '>' && str[var->i] != ' ' \
		&& str[var->i] != '|' && str[var->i] != '\'' && str[var->i] != '"' \
		&& str[var->i] != '\0') && !var->qutrg && var->rdrtrg))
	{
		var->rcn[var->j][var->k] = ++var->cnum;
		if (str[var->i + 1] == '<' || str[var->i + 1] == '>' \
		|| str[var->i + 1] == ' ' || str[var->i + 1] == '|')
			var->rdrtrg = FALSE;
	}
}

int	**find_rdr_chars(char *str, char rdr, t_parse *data)
{
	t_var	var;

	var = (t_var){0};
	if (init_rdr_vars(&var, data, str, rdr))
		return (NULL);
	var.rcn = ft_calloc(var.parts_num, sizeof(int *));
	while (++var.i < var.parts_num)
		var.rcn[var.i] = ft_calloc(var.rnum[var.i], sizeof(int));
	var.i = -1;
	while (++var.i < var.len && str[var.i])
	{
		check_quout(&var, str);
		if (str[var.i] == '|' && !var.qutrg && !var.rdrtrg \
			&& var.j < var.parts_num)
		{
			var.j++;
			var.k = -1;
		}
		check_type(&var, str, rdr);
		if (to_cont(&var, str))
			continue ;
		count_rdr_chars(&var, str);
	}
	return (var.rcn);
}
