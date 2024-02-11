/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tabs_to_spc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:38:22 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/11 16:05:04 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	init_contabvar(t_var *var, char *str)
{
	var->i = -1;
	var->j = 0;
	var->len = ft_strlen(str);
	var->ret = NULL;
	var->qutrg = FALSE;
	var->qchr = '\0';
}

char	*conv_tabs2spcs(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_contabvar(&var, str);
	var.ret = ft_calloc(var.len + 1, sizeof(char));
	while (++var.i < var.len)
	{
		if ((str[var.i] == '\'' || str[var.i] == '"') && !var.qutrg)
		{
			var.qchr = str[var.i];
			var.qutrg = TRUE;
		}
		else if (str[var.i] == var.qchr && var.qutrg)
		{
			var.qchr = '\0';
			var.qutrg = FALSE;
		}
		if (str[var.i] == '\t' && !var.qutrg)
			str[var.i] = ' ';
		var.ret[var.j++] = str[var.i];
	}
	var.ret[var.j] = '\0';
	free_set_null(str);
	return (var.ret);
}

void	if_else_conv(t_var *var, char *str)
{
	if (var->rdrtrg)
	{
		if (str[var->i + 1] == ' ' || str[var->i + 1] == '<' \
		|| str[var->i + 1] == '>' || str[var->i + 1] == '|' \
		|| str[var->i + 1] == '\0')
		{
			var->i++;
			var->rdrtrg = FALSE;
		}
		var->nordr[var->j++] = ' ';
	}
	else
		var->nordr[var->j++] = str[var->i++];
}
