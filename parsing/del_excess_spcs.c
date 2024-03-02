/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_excess_spcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:24:39 by alsaeed           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/13 21:29:41 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/20 17:50:38 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	jump_over_spaces(char *str, int *i)
{
	(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	(*i)--;
}

static t_bool	delco_consqut(char *str, t_var *var)
{
	if (((str[var->i] == '"' && str[var->i + 1] == '"') \
	|| (str[var->i] == '\'' && str[var->i + 1] == '\'')) \
	&& !var->qutrg)
	{
		var->size += 2;
		var->i++;
		return (TRUE);
	}
	return (FALSE);
}

void	jmp_mid_spcs(t_var *var, char *str, int mode)
{
	if (str[var->i] == ' ' && str[var->i + 1] == ' ' && !var->qutrg)
	{
		if (mode == 0 && str[var->i] != ' ' && (var->i < var->len - 1 \
		|| (var->i == var->len - 1 && str[var->len - 1] != ' ')))
			var->size++;
		else if (mode == 1 && str[var->i] != ' ' && (var->i < var->len - 1 \
		|| (var->i == var->len - 1 && str[var->len - 1] != ' ')))
			var->ret[var->j++] = str[var->i];
		var->i++;
	}
	if (str[var->i] == ' ' && !var->qutrg)
	{
		if (mode == 0)
			var->size++;
		else if (mode == 1)
			var->ret[var->j++] = str[var->i++];
	}
	while (str[var->i] == ' ' && !var->qutrg)
		var->i++;
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qutrg = TRUE;
		var->qchr = str[var->i];
	}
}

int	size_without_spcs(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_del_exspc(&var, str, 0);
	while (++var.i < var.len)
	{
		if (delco_consqut(str, &var))
			continue ;
		if ((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.qutrg = TRUE;
			var.qchr = str[var.i];
		}
		else if (str[var.i] == var.qchr && var.qutrg)
		{
			var.qchr = '\0';
			var.qutrg = FALSE;
		}
		jmp_mid_spcs(&var, str, 0);
		if (var.i < var.len - 1 || (var.i == var.len - 1 \
		&& str[var.len - 1] != ' '))
			var.size++;
	}
	return (var.size);
}

char	*delete_excess_spcs(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_del_exspc(&var, str, 1);
	while (++var.i < var.len)
	{
<<<<<<< HEAD
		if ((str[var.i] == '"' && str[var.i + 1] == '"') \
		|| (str[var.i] == '\'' && str[var.i + 1] == '\''))
		{
			var.i++;
			continue;
		}
		if ((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.qutrg = TRUE;
			var.qchr = str[var.i];
		}
		else if (str[var.i] == var.qchr && var.qutrg)
		{
			var.qchr = '\0';
			var.qutrg = FALSE;
		}
=======
		if (del_consqut(str, &var))
			continue ;
>>>>>>> main
		jmp_mid_spcs(&var, str, 1);
		if (var.i < var.len - 1 || (var.i == var.len - 1 \
		&& str[var.len - 1] != ' '))
			var.ret[var.j++] = str[var.i];
	}
	if (var.ret[var.j] == ' ')
		var.ret[var.j] = '\0';
	else if (var.ret[var.j])
		var.ret[++var.j] = '\0';
	free_set_null((void **)&str);
	return (var.ret);
}
