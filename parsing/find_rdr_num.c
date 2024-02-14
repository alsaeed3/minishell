/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rdr_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:47:49 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/14 17:25:00 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	init_rdr_num(t_var *var, char *str)
{
	var->i = -1;
	var->j = 0;
	var->k = 0;
	var->l = -1;
	var->len = ft_strlen(str);
	var->parts_num = find_parts_num(str);
	var->qutrg = FALSE;
	var->qchr = '\0';
	var->rdrtrg = FALSE;
	var->rnum = NULL;
	var->rcn = NULL;
}

void	find_tot_rdr(char rdr, t_parse *data)
{
	if (rdr == '<')
		data->tot_inredir++;
	else if (rdr == '>')
		data->tot_outredir++;
}

int	ret_rnum(char rdr, t_parse *data)
{
	if (rdr == '<')
		return (data->tot_inredir);
	else if (rdr == '>')
		return (data->tot_outredir);
	return (0);
}

void	quote_context(char *str, t_var *var)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qchr = str[var->i];
		var->qutrg = TRUE;
	}
	else if ((str[var->i] == var->qchr) && var->qutrg)
	{
		var->qchr = '\0';
		var->qutrg = FALSE;
	}
}

int	*find_rdr_num(char *str, char rdr, t_parse *data)
{
	t_var	var;

	var = (t_var){0};
	init_rdr_num(&var, str);
	var.rnum = ft_calloc(var.parts_num, sizeof(int));
	while (++var.i < var.len)
	{
		if (rdr_consqut(str, &var))
			continue ;
		if (str[var.i] == '|' && !var.qutrg && var.j < var.parts_num)
			var.j++;
		if (var.i < var.len - 1 && (str[var.i] == rdr && str[var.i + 1] != rdr \
			&& (var.i == 0 || str[var.i - 1] != rdr)) && !var.qutrg)
		{
			find_tot_rdr(rdr, data);
			var.rnum[var.j]++;
		}
		else if (var.i < var.len - 1 && (str[var.i] == rdr \
			&& str[var.i + 1] == rdr) && !var.qutrg)
		{
			find_tot_rdr(rdr, data);
			var.rnum[var.j]++;
		}
	}
	return (var.rnum);
}
