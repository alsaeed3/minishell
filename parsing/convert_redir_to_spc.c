/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir_to_spc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:03:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/18 00:58:11 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	init_nordr_vars(t_var *var, char *str)
{
	var->rdrtrg = FALSE;
	var->qutrg = FALSE;
	var->len = ft_strlen(str);
	var->i = -1;
	var->size = 0;
	var->size = ft_strlen(str);
	var->nordr = ft_calloc((var->size + 1), sizeof(char));
}

char	*conv_redir2spcs(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_nordr_vars(&var, str);
	while (++var.i < var.len && str[var.i])
	{
		if (cons_quot_conv(&var, str))
			continue ;
		check_quotation(&var, str);
		check_rdr(&var, str);
		check_pipe(&var, str);
		if (continue_conv(&var, str))
			continue ;
		if (!var.rdrtrg && var.i < var.len)
			var.nordr[var.j++] = str[var.i];
		else if (var.i < var.len && str[var.i] != ' ' && var.rdrtrg)
			var.nordr[var.j++] = ' ';
	}
	if (var.nordr || var.nordr[var.j])
		var.nordr[var.j] = '\0';
	free_set_null((void **)&str);
	return (var.nordr);
}
