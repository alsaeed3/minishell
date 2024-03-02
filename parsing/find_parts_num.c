/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_parts_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:45:33 by alsaeed           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/31 23:14:04 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	find_parts_num(char *str)
{
	int		i;
	int		parts_num;
	t_bool	quo_trigger;
	char	quo_char;
	int		len;

	quo_trigger = FALSE;
	quo_char = '\0';
	parts_num = 1;
	len = (int)ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quo_trigger)
		{
			quo_char = str[i];
			quo_trigger = TRUE;
		}
		else if ((str[i] == quo_char) && quo_trigger)
			quo_trigger = false;
		if (str[i] == '|' && !quo_trigger)
			parts_num++;
	}
	return (parts_num);
=======
/*   Updated: 2024/02/19 19:23:04 by alsaeed          ###   ########.fr       */
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
>>>>>>> main
}

t_bool	init_rdr_vars(t_var *var, t_parse *data, char *str, char rdr)
{
<<<<<<< HEAD
=======
	*var = (t_var){0};
>>>>>>> main
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
