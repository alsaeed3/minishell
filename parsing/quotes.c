/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:08:50 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/13 21:29:41 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	init_vars(t_var *var, char *str)
{
	var->i = -1;
	var->qutrg = FALSE;
	var->qchr = '\0';
	var->len = ft_strlen(str);
}

t_bool	check_quotes(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_vars(&var, str);
	while (++var.i < var.len)
	{
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
			while (++var.i < var.len)
			{
				if (str[var.i] == var.qchr)
				{
					var.qutrg = FALSE;
					var.qchr = '\0';
					break ;
				}
			}
		}
	}
	return (var.qutrg);
}
