/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:08:50 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/06 21:11:35 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

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

void	remove_cmdline_quotes(char *str, char **ret, int char_num)
{
	int	i;
	int	k;
	int	trigger;
	int	len;

	i = -1;
	k = -1;
	len = (int)ft_strlen(str);
	*ret = malloc(sizeof(char) * (char_num + 1));
	while (++i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			trigger = (int)str[i];
			while (++i < len)
			{
				if (str[i] == trigger)
					break ;
				(*ret)[++k] = str[i];
			}
		}
		if (str[i] != ' ' && str[i] != '\'' && str[i] != '"')
			(*ret)[++k] = str[i];
	}
	(*ret)[++k] = '\0';
}
