/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rdr_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:57:18 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/26 21:25:33 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// to find each infile/heredoc file name characters and store them into
// a double pointer to use it later in mallocing

void	jump_over_quote(char *cmd_line, int *i, int len)
{
	char	quo_char;

	if (cmd_line[*i] == '\'' || cmd_line[*i] == '"')
		quo_char = cmd_line[*i];
	(*i)++;
	while (*i < len)
	{
		if (cmd_line[*(i)] == quo_char)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
}

void	check_type(t_var *var, char *str, char rdr)
{
	if (var->i < var->len - 1 && (str[var->i] == rdr && str[var->i + 1] \
	!= rdr && (var->i == 0 || str[var->i - 1] != rdr)) \
	&& !var->rtrg && !var->qtrg && var->k < var->rnum[var->j])
	{
		var->cnum = 0;
		var->rtrg = TRUE;
		var->k++;
		var->i++;
		if (str[var->i] == ' ')
			var->i++;
	}
	else if (var->i < var->len - 1 && (str[var->i] == rdr && str[var->i + 1] \
	== rdr) && !var->rtrg && !var->qtrg && var->k < var->rnum[var->j])
	{
		var->cnum = 0;
		var->rtrg = TRUE;
		var->k++;
		var->i += 2;
		if (str[var->i] == ' ')
			var->i++;
	}
	else if ((str[var->i] == '<' || str[var->i] == '>' || str[var->i] == ' ' \
	|| str[var->i] == '|' || str[var->i] != var->qchr) && var->qtrg \
	&& var->rtrg)
		var->rcn[var->j][var->k] = ++var->cnum;
}

static t_bool	to_cont(t_var *var, char *str)
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
	return (FALSE);
}

static t_bool	count_rdr_chars(t_var var, char *str)
{
	if (((str[var.i] != '<' && str[var.i] != '>' && str[var.i] != ' ' \
		&& str[var.i] != '|' && str[var.i] != '\'' && str[var.i] != '"' \
		&& str[var.i] != '\0') && !var.qtrg && var.rtrg))
		return (TRUE);
	return (FALSE);
}

int	**find_rdr_chars(char *str, char rdr, t_parse *data)
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
	var.rcn = ft_calloc(var.parts_num, sizeof(int *));
	while (++var.i < var.parts_num)
		var.rcn[var.i] = ft_calloc(var.rnum[var.i], sizeof(int));
	var.i = -1;
	while (++var.i < var.len && str[var.i])
	{
		if (str[var.i] == '|' && !var.qtrg && !var.rtrg \
			&& var.j < var.parts_num)
		{
			var.j++;
			var.k = -1;
		}
		check_type(&var, str, rdr);
		if (to_cont(&var, str))
			continue ;
		if (count_rdr_chars(var, str))
		{
			var.rcn[var.j] \
			[var.k] = \
			++var.cnum;
			if (str[var.i + 1] == '<' || str[var.i + 1] == '>' \
				|| str[var.i + 1] == ' ' || str[var.i + 1] == '|')
				var.rtrg = FALSE;
		}
	}
	return (var.rcn);
}
