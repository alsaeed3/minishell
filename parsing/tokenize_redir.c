/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:01:18 by alsaeed           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/13 21:29:41 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/19 16:22:08 by alsaeed          ###   ########.fr       */
>>>>>>> main
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

void	set_token(t_var *var, char *str, char rdr)
{
	if (var->i < var->len - 1 && str[var->i] == rdr && str[var->i + 1] != rdr \
	&& (var->i == 0 || str[var->i - 1] != rdr) && !var->qutrg)
		var->tkn[var->j][++var->k] = 0;
	else if (var->i < var->len - 1 && str[var->i] == rdr \
	&& str[var->i + 1] == rdr && !var->qutrg)
		var->tkn[var->j][++var->k] = 1;
}

int	**tokenize_redir(char *str, t_parse *data, char rdr)
{
	t_var	var;

	if (init_rdr_vars(&var, data, str, rdr))
		return (NULL);
	var.tkn = ft_calloc(var.parts_num, sizeof(int *));
	while (++var.i < var.parts_num)
		var.tkn[var.i] = ft_calloc(var.rnum[var.i], sizeof(int));
	var.i = -1;
	while (++var.i < var.len)
	{
<<<<<<< HEAD
		if ((str[var.i] == '"' && str[var.i + 1] == '"') \
		|| (str[var.i] == '\'' && str[var.i + 1] == '\''))
		{
			var.i++;
			continue;
=======
		if (((str[var.i] == '"' && str[var.i + 1] == '"') \
		|| (str[var.i] == '\'' && str[var.i + 1] == '\'')) && !var.qutrg)
		{
			var.i++;
			continue ;
>>>>>>> main
		}
		check_quot(&var, str);
		if (str[var.i] == '|' && !var.qutrg)
		{
			var.j++;
			var.k = -1;
		}
		set_token(&var, str, rdr);
	}
	return (var.tkn);
}
