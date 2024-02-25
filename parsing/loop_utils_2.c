/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:55:44 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/19 19:25:28 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

t_bool	cnsqut_cmd_num(t_cvr *cvr, char *str)
{
	if (((str[cvr->i] == '"' && str[cvr->i + 1] == '"') \
	|| (str[cvr->i] == '\'' && str[cvr->i + 1] == '\'')) \
	&& !cvr->qutrg)
	{
		if (cvr->qutrg)
		{
			cvr->chars_num += 2;
			cvr->chrn[cvr->j][cvr->k] = cvr->chars_num;
		}
		cvr->i++;
		return (TRUE);
	}
	count_qut_pipe(cvr, str);
	if (str[cvr->i] == ' ' && (cvr->i == 0 || str[cvr->i - 1] != ' ') \
	&& (cvr->i == 0 || str[cvr->i - 1] != '|') && !cvr->qutrg)
	{
		cvr->k++;
		cvr->chars_num = 0;
	}
	return (FALSE);
}

t_bool	null_deli(t_parse *data, t_hvr *hvr)
{
	if (data->inputs_redirections[hvr->i][hvr->j] == NULL \
	&& data->inputs_redirections[hvr->i][hvr->j + 1] == NULL \
	&& data->inputs_tokens[hvr->i][hvr->j] == 1)
		return (TRUE);
	return (FALSE);
}

t_bool	rdr_consqut(char *str, t_var *var)
{
	if (var->i < var->len -1 && ((str[var->i] == '"' && str[var->i + 1] == '"') \
	|| (str[var->i] == '\'' && str[var->i + 1] == '\'')) \
	&& !var->qutrg)
	{
		var->i++;
		return (TRUE);
	}
	quote_context(str, var);
	return (FALSE);
}

t_bool	del_consqut(char *str, t_var *var)
{
	if (((str[var->i] == '"' && str[var->i + 1] == '"') \
	|| (str[var->i] == '\'' && str[var->i + 1] == '\'')) \
	&& !var->qutrg)
	{
		var->ret[var->j++] = str[var->i];
		var->ret[var->j++] = str[var->i + 1];
		var->i++;
		return (TRUE);
	}
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qutrg = TRUE;
		var->ret[var->j++] = str[var->i];
		var->qchr = str[var->i++];
	}
	else if (str[var->i] == var->qchr && var->qutrg)
	{
		var->qchr = '\0';
		var->qutrg = FALSE;
		var->ret[var->j++] = str[var->i++];
	}
	return (FALSE);
}
