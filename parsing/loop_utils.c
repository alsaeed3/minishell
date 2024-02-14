/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:21:50 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/14 17:05:40 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

t_bool	check_cons_qut(t_var *var, char *str)
{
	if ((str[var->i] == '"' && str[var->i + 1] == '"') \
	|| (str[var->i] == '\'' && str[var->i + 1] == '\''))
	{
		if (var->qutrg)
		{
			var->cnum += 2;
			var->rcn[var->j][var->k] = var->cnum;
		}
		var->i++;
		return (TRUE);
	}
	check_quout(var, str);
	return (FALSE);
}

t_bool	cons_quot_hold(t_var *var, char *str)
{
	if ((str[var->i] == '"' && str[var->i + 1] == '"') \
	|| (str[var->i] == '\'' && str[var->i + 1] == '\''))
	{
		if (var->qutrg)
		{
			var->rnms[var->j][var->k][var->l++] = str[var->i];
			var->rnms[var->j][var->k][var->l++] = str[var->i + 1];
		}
		var->i++;
		return (TRUE);
	}
	hold_rdr_1(var, str);
	return (FALSE);
}

t_bool	cons_quot_dollar(t_var *var, char *str)
{
	if ((str[var->i] == '"' && str[var->i + 1] == '"') \
	|| (str[var->i] == '\'' && str[var->i + 1] == '\''))
	{
		var->ret[var->j++] = str[var->i];
		var->ret[var->j++] = str[var->i + 1];
		var->i++;
		return (TRUE);
	}
	sd_quote_trg(var, str);
	return (FALSE);
}

t_bool	cons_quot_conv(t_var *var, char *str)
{
	if ((str[var->i] == '"' && str[var->i + 1] == '"') \
	|| (str[var->i] == '\'' && str[var->i + 1] == '\''))
	{
		var->nordr[var->j++] = str[var->i];
		var->nordr[var->j++] = str[var->i + 1];
		var->i++;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	cons_quot_cmd(t_cvr *cvr, char *str)
{
	if ((str[cvr->i] == '"' && str[cvr->i + 1] == '"') \
	|| (str[cvr->i] == '\'' && str[cvr->i + 1] == '\''))
	{
		if (cvr->qutrg)
		{
			cvr->cmds[cvr->j][cvr->k][cvr->l++] = str[cvr->i];
			cvr->cmds[cvr->j][cvr->k][cvr->l++] = str[cvr->i + 1];
		}
		cvr->i++;
		return (TRUE);
	}
	check_qut_pipe(cvr, str);
	return (FALSE);
}
