/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_parts_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:45:33 by alsaeed           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/13 21:29:56 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/19 19:23:04 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"
<<<<<<< HEAD
=======

static void	init_parts_num_vars(t_var *var, char *str)
{
	*var = (t_var){0};
	var->qutrg = FALSE;
	var->qchr = '\0';
	var->parts_num = 1;
	var->len = (int)ft_strlen(str);
	var->i = -1;
}
>>>>>>> main

int	find_parts_num(char *str)
{
	t_var	var;

	init_parts_num_vars(&var, str);
	while (++var.i < var.len)
	{
<<<<<<< HEAD
		if ((str[i] == '"' && str[i + 1] == '"') \
		|| (str[i] == '\'' && str[i + 1] == '\''))
		{
			i++;
			continue;
		}
		if ((str[i] == '"' || str[i] == '\'') && !quo_trigger)
=======
		if (var.i < var.len -1 && ((str[var.i] == '"' && str[var.i + 1] == '"') \
		|| (str[var.i] == '\'' && str[var.i + 1] == '\'')) \
		&& !var.qutrg)
>>>>>>> main
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
