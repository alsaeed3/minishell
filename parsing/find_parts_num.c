/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_parts_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:45:33 by alsaeed           #+#    #+#             */
/*   Updated: 2024/09/29 10:28:38 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	init_parts_num_vars(t_var *var, char *str)
{
	*var = (t_var){0};
	var->qutrg = FALSE;
	var->qchr = '\0';
	var->parts_num = 1;
	var->len = (int)ft_strlen(str);
	var->i = -1;
}

int	find_parts_num(char *str)
{
	t_var	var;

	init_parts_num_vars(&var, str);
	while (++var.i < var.len)
	{
		if (var.i < var.len -1 && ((str[var.i] == '"' && str[var.i + 1] == '"') \
		|| (str[var.i] == '\'' && str[var.i + 1] == '\'')) \
		&& !var.qutrg)
		{
			var.i++;
			continue ;
		}
		if ((str[var.i] == '"' || str[var.i] == '\'') && !var.qutrg)
		{
			var.qchr = str[var.i];
			var.qutrg = TRUE;
		}
		else if ((str[var.i] == var.qchr) && var.qutrg)
			var.qutrg = FALSE;
		if (str[var.i] == '|' && !var.qutrg)
			var.parts_num++;
	}
	return (var.parts_num);
}

t_bool	init_rdr_vars(t_var *var, t_parse *data, char *str, char rdr)
{
	*var = (t_var){0};
	var->i = -1;
	var->j = 0;
	var->k = -1;
	var->l = -1;
	var->len = ft_strlen(str);
	var->parts_num = find_parts_num(str);
	var->qutrg = FALSE;
	var->qchr = '\0';
	var->rdrtrg = FALSE;
	var->rnum = NULL;
	var->rcn = NULL;
	if (rdr == '<' && data->tot_inredir)
		var->rnum = data->in_rdr_num;
	else if (rdr == '>' && data->tot_outredir)
		var->rnum = data->out_rdr_num;
	if (rdr == '<' && !data->tot_inredir)
		return (TRUE);
	else if (rdr == '>' && !data->tot_outredir)
		return (TRUE);
	return (FALSE);
}
