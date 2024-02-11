/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:01:18 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/11 11:37:59 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	check_quot(t_var *var, char *str)
{
	if ((str[var->i] == '"' || str[var->i] == '\'') && !var->qutrg)
	{
		var->qchr = str[var->i++];
		var->qutrg = TRUE;
		if (str[var->i] == var->qchr)
		{
			var->qchr = '\0';
			var->qutrg = FALSE;
		}
	}
	else if ((str[var->i] == var->qchr) && var->qutrg)
	{
		var->qchr = '\0';
		var->qutrg = FALSE;
	}
}

int	**tokenize_redir(char *str, t_parse *data, char rdr)
{
	t_var	var;

	var = (t_var){0};
	if (init_rdr_vars(&var, data, str, rdr))
		return (NULL);
	var.tkn = ft_calloc(var.parts_num, sizeof(int *));
	while (++var.i < var.parts_num)
		var.tkn[var.i] = ft_calloc(var.rnum[var.i], sizeof(int));
	var.i = -1;
	while (++var.i < var.len)
	{
		check_quot(&var, str);
		if (str[var.i] == '|' && !var.qutrg)
		{
			var.j++;
			var.k = -1;
		}
		if (var.i < var.len - 1 && str[var.i] == rdr && str[var.i + 1] != rdr \
		&& (var.i == 0 || str[var.i - 1] != rdr) && !var.qutrg)
			var.tkn[var.j][++var.k] = 0;
		else if (var.i < var.len - 1 && str[var.i] == rdr \
		&& str[var.i + 1] == rdr && !var.qutrg)
			var.tkn[var.j][++var.k] = 1;
	}
	return (var.tkn);
}
