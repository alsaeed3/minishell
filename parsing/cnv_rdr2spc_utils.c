/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnv_rdr2spc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:15:02 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/07 14:37:03 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	check_rdrc(t_var *var, char *str)
{
	if (var->i < var->len - 1 && ((str[var->i] == '<' \
	&& str[var->i + 1] != '<' && (var->i == 0 || str[var->i - 1] != '<')) \
	|| (str[var->i] == '>' && str[var->i + 1] != '>' && (var->i == 0 \
	|| str[var->i - 1] != '>'))) && !var->rdrtrg && !var->qutrg)
	{
		var->rdrtrg = TRUE;
		var->i++;
		var->j++;
		if (str[var->i] == ' ')
			var->j++;
	}
	else if (var->i < var->len - 1 && ((str[var->i] == '<' \
	&& str[var->i + 1] == '<') || (str[var->i] == '>' \
	&& str[var->i + 1] == '>')) && !var->rdrtrg && !var->qutrg)
	{
		var->rdrtrg = TRUE;
		var->i += 2;
		var->j += 2;
		if (str[var->i] == ' ')
			var->j++;
	}
}

void	check_quotation(t_var *var, char *str)
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:15:02 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/20 18:13:25 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

t_bool	check_quotation(t_var *var, char *str)
>>>>>>> main
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qchr = str[var->i];
		var->qutrg = TRUE;
		if (var->rdrtrg)
<<<<<<< HEAD
		{
			var->i++;
			var->nordr[var->j++] = ' ';
		}
		else
			var->nordr[var->j++] = str[var->i++];
=======
			var->nordr[var->j++] = ' ';
		else
			var->nordr[var->j++] = str[var->i];
		return (TRUE);
>>>>>>> main
	}
	else if ((str[var->i] == var->qchr) && var->qutrg)
	{
		var->qchr = '\0';
		var->qutrg = FALSE;
<<<<<<< HEAD
		if (var->rdrtrg)
		{
			if (str[++var->i] == ' ')
				var->rdrtrg = FALSE;
			var->nordr[var->j++] = ' ';
		}
		else
			var->nordr[var->j++] = str[var->i++];
	}
=======
		if_else_conv(var, str);
		return (TRUE);
	}
	return (FALSE);
>>>>>>> main
}

void	check_rdr(t_var *var, char *str)
{
	if (var->i < var->len - 1 && ((str[var->i] == '<' \
	&& str[var->i + 1] != '<' && (var->i == 0 || str[var->i - 1] != '<')) \
	|| (str[var->i] == '>' && str[var->i + 1] != '>' && (var->i == 0 \
	|| str[var->i - 1] != '>'))) && !var->rdrtrg && !var->qutrg)
	{
		var->rdrtrg = TRUE;
		var->i++;
		var->nordr[var->j++] = ' ';
		if (str[var->i] == ' ')
			var->nordr[var->j++] = ' ';
	}
	else if (var->i < var->len - 1 && ((str[var->i] == '<' \
	&& str[var->i + 1] == '<') || (str[var->i] == '>' \
	&& str[var->i + 1] == '>')) && !var->rdrtrg && !var->qutrg)
	{
		var->rdrtrg = TRUE;
		var->i += 2;
		var->nordr[var->j++] = ' ';
		var->nordr[var->j++] = ' ';
		if (str[var->i] == ' ')
			var->nordr[var->j++] = ' ';
	}
}

<<<<<<< HEAD
t_bool	continue_conv(t_var *var, char *str)
{
	if (((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg))
	{
		var->nordr[var->j++] = str[var->i];
		var->qutrg = TRUE;
		return (TRUE);
	}
	else if (str[var->i] == var->qchr && var->qutrg)
	{
		var->nordr[var->j++] = str[var->i];
		var->qutrg = FALSE;
		return (TRUE);
	}
	if (((str[var->i] != '<' && str[var->i] != '>' && str[var->i] != ' ' \
	&& str[var->i] != '|' && str[var->i] != '\'' && str[var->i] != '"') \
	&& !var->qutrg && var->rdrtrg))
=======
static void	if_else_cont_conv(t_var *var, char *str)
{
	if (!var->rdrtrg)
		var->nordr[var->j++] = str[var->i];
	else
		var->nordr[var->j++] = ' ';
	var->qchr = str[var->i];
	var->qutrg = TRUE;
}

t_bool	continue_conv(t_var *var, char *str)
{
	if (var->i < var->len && ((str[var->i] == '\'' || str[var->i] == '"') \
	&& !var->qutrg))
	{
		if_else_cont_conv(var, str);
		return (TRUE);
	}
	else if (var->i < var->len && str[var->i] == var->qchr && var->qutrg)
	{
		var->nordr[var->j++] = str[var->i];
		var->qchr = '\0';
		var->qutrg = FALSE;
		return (TRUE);
	}
	if (var->i < var->len && ((str[var->i] != '<' && str[var->i] != '>' \
	&& str[var->i] != ' ' && str[var->i] != '|' && str[var->i] != '\'' \
	&& str[var->i] != '"') && !var->qutrg && var->rdrtrg))
>>>>>>> main
	{
		var->nordr[var->j++] = ' ';
		return (TRUE);
	}
	return (FALSE);
}

<<<<<<< HEAD
void	check_pipe(t_var *var, char *str, int mode)
{
	if ((str[var->i] == '|' || (str[var->i] == ' ' && \
	(var->i == 0 || str[var->i - 1] != '<') && (var->i == 0 \
	|| str[var->i - 1] != '>'))) && var->rdrtrg && !var->qutrg)
	{
		if (str[var->i] == ' ' && mode == 0)
			var->j++;
		else if (str[var->i] == ' ' && mode == 1)
			var->nordr[var->j++] = ' ';
		var->rdrtrg = FALSE;
	}
=======
void	check_pipe(t_var *var, char *str)
{
	if (var->i < var->len && (str[var->i] == '|' || (str[var->i] == ' ' \
	&& (var->i == 0 || str[var->i - 1] != '<') && (var->i == 0 \
	|| str[var->i - 1] != '>'))) && var->rdrtrg && !var->qutrg)
		var->rdrtrg = FALSE;
>>>>>>> main
}
