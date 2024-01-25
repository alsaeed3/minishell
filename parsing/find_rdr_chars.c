/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rdr_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 00:57:18 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/25 21:12:21 by alsaeed          ###   ########.fr       */
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
			break;
		}
		(*i)++;
	}
}

void	check_type(t_var *var, char *str, char rdr)
{
	if (var->i < var->len - 1 && (str[var->i] == rdr && str[var->i + 1] \
	!= rdr && (var->i == 0 || str[var->i - 1] != rdr)) \
	&& !var->rdrtrg && !var->qutrg && var->k < var->rdrnum[var->j])
	{
		var->chrnum = 0;
		var->rdrtrg = TRUE;
		var->k++;
		var->i++;
		if (str[var->i] == ' ')
			var->i++;
	}
	else if (var->i < var->len - 1 && (str[var->i] == rdr \
	&& str[var->i + 1] == rdr) && !var->rdrtrg && !var->qutrg \
	&& var->k < var->rdrnum[var->j])
	{
		var->chrnum = 0;
		var->rdrtrg = TRUE;
		var->k++;
		var->i += 2;
		if (str[var->i] == ' ')
			var->i++;
	}
	else if ((str[var->i] == '<' || str[var->i] == '>' || str[var->i] == ' ' \
	|| str[var->i] == '|' || str[var->i] != var->quchr) && var->qutrg \
	&& var->rdrtrg)
		var->rcn[var->j][var->k] = ++var->chrnum;
}

static t_bool	to_cont(t_var *var, char *str)
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
	return (FALSE);
}

static t_bool	count_rdr_chars(t_var var, char *str)
{
	if (((str[var.i] != '<' && str[var.i] != '>' && str[var.i] != ' ' \
		&& str[var.i] != '|' && str[var.i] != '\'' && str[var.i] != '"' \
		&& str[var.i] != '\0') && !var.qutrg && var.rdrtrg))
		return (TRUE);
	return (FALSE);
}

int	**find_rdr_chars(char *str, char rdr)
{
	t_var	var;

	init_rdr_vars(&var, str, 2, rdr);
	while (++var.i < var.len && str[var.i])
	{

		if (str[var.i] == '|' && !var.qutrg && !var.rdrtrg \
			&& var.j < var.parts_num)
		{
			var.j++;
			var.k = -1;
		}
		check_type(&var, str, rdr);
		if (to_cont(&var, str))
			continue;
		// int i = 0;
		if (count_rdr_chars(var, str))
		{
			printf("var.j: %d var.k: %d\n", var.j, var.k);
			// printf("var.chrnum: %d\n", var.chrnum);
			var.rcn[var.j] \
			[var.k] = \
			++var.chrnum;
			if (str[var.i + 1] == '<' || str[var.i + 1] == '>' \
				|| str[var.i + 1] == ' ' || str[var.i + 1] == '|')
				var.rdrtrg = FALSE;
		}
	}
	return (var.rcn);
}
