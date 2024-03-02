/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_excess_spcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:24:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/06 20:59:05 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:24:39 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/20 17:50:38 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"
>>>>>>> main

void	jump_over_spaces(char *str, int *i)
{
	(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	(*i)--;
}

<<<<<<< HEAD
=======
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

>>>>>>> main
void	jmp_mid_spcs(t_var *var, char *str, int mode)
{
	if (str[var->i] == ' ' && str[var->i + 1] == ' ' && !var->qutrg)
	{
<<<<<<< HEAD
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
=======
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
>>>>>>> main
	}
}

int	size_without_spcs(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_del_exspc(&var, str, 0);
	while (++var.i < var.len)
	{
<<<<<<< HEAD
=======
		if (delco_consqut(str, &var))
			continue ;
>>>>>>> main
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
<<<<<<< HEAD
		var.size++;
=======
		if (var.i < var.len - 1 || (var.i == var.len - 1 \
		&& str[var.len - 1] != ' '))
			var.size++;
>>>>>>> main
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
<<<<<<< HEAD
	if (var.ret[var.j])
		var.ret[++var.j] = '\0';
	free_set_null(str);
=======
	if (var.ret[var.j] == ' ')
		var.ret[var.j] = '\0';
	else if (var.ret[var.j])
		var.ret[++var.j] = '\0';
	free_set_null((void **)&str);
>>>>>>> main
	return (var.ret);
}
