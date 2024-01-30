/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_excess_spcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:24:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/30 21:49:28 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

static void	jump_over_spaces(char *str, int *i)
{
	(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	(*i)--;
}

void	init_del_exspc(t_var *var, char *str)
{
	var->len = ft_strlen(str);
	var->i = -1;
	var->j = 0;
	var->size = 0;
	if (str[0] == ' ')
		jump_over_spaces(str, &var->i);
	var->qutrg = FALSE;
}

void	jmp_mid_spcs(t_var *var, char *str, int mode)
{
	if (str[var->i] == ' ' && str[var->i + 1] == ' ' && !var->qutrg)
	{
		if (mode == 0)
			var->size++;
		else if (mode == 1)
		{
			if (var->i < var->len - 1 || (var->i == var->len - 1 \
			&& str[var->len - 1] != ' '))
				var->ret[var->j++] = str[var->i];
		}
		while (str[var->i] == ' ')
			var->i++;
		if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
		{
			var->qutrg = TRUE;
			var->qchr = str[var->i];
		}
	}
}

static int	size_without_spcs(char *str)
{
	t_var	var;

	init_del_exspc(&var, str);
	while (++var.i < var.len)
	{
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
		var.size++;
	}
	return (var.size);
}

char	*delete_excess_spcs(char *str)
{
	t_var	var;

	init_del_exspc(&var, str);
	var.size = size_without_spcs(str);
	var.ret = ft_calloc(var.size + 1, sizeof(char));
	while (++var.i < var.len)
	{
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
		jmp_mid_spcs(&var, str, 1);
		if (var.i < var.len - 1 || (var.i == var.len - 1 \
		&& str[var.len - 1] != ' '))
			var.ret[var.j++] = str[var.i];
	}
	if (var.ret[var.j])
		var.ret[++var.j] = '\0';
	return (var.ret);
}
