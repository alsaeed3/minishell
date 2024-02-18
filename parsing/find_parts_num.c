/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_parts_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:45:33 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/18 23:01:55 by alsaeed          ###   ########.fr       */
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
		if (((str[var.i] == '"' && str[var.i + 1] == '"') \
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

int	*all_rdr_num(int *in_rdr_num, int *out_rdr_num, int parts_num)
{
	int	*all_rdr_num;
	int	i;

	if (!in_rdr_num && !out_rdr_num)
		return (NULL);
	all_rdr_num = ft_calloc(parts_num, sizeof(int));
	if (!all_rdr_num)
		return (NULL);
	i = -1;
	while (++i < parts_num)
	{
		if (in_rdr_num && in_rdr_num[i] && out_rdr_num && out_rdr_num[i])
			all_rdr_num[i] = in_rdr_num[i] + out_rdr_num[i];
		else if (in_rdr_num && in_rdr_num[i])
			all_rdr_num[i] = in_rdr_num[i];
		else if (out_rdr_num && out_rdr_num[i])
			all_rdr_num[i] = out_rdr_num[i];
	}
	return (all_rdr_num);
}

t_bool	init_tkn_vars(t_var *var, t_parse *data, char *str)
{
	if (!data->in_rdr_num && !data->out_rdr_num)
		return (TRUE);
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
	var->rcn = NULL;
	var->rnum = all_rdr_num(data->in_rdr_num, data->out_rdr_num, var->parts_num);
	if (!var->rnum)
		return (TRUE);
	data->all_rdr_num = var->rnum;
	return (FALSE);
}

