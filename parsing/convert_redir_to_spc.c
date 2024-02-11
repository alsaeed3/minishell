/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_redir_to_spc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 01:03:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/11 13:38:28 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	check_quota(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->qchr = str[var->i];
		var->qutrg = TRUE;
		var->i++;
		var->j++;
	}
	else if ((str[var->i] == var->qchr) && var->qutrg)
	{
		var->qchr = '\0';
		var->qutrg = FALSE;
		var->i++;
		if (var->rdrtrg)
		{
			if (str[var->i] == ' ')
				var->rdrtrg = FALSE;
		}
		var->j++;
	}
}

t_bool	continue_count(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') && !var->qutrg)
	{
		var->j++;
		var->qutrg = TRUE;
		var->qchr = str[var->i];
		return (TRUE);
	}
	else if (str[var->i] == var->qchr && var->qutrg)
	{
		var->j++;
		var->qchr = '\0';
		var->qutrg = FALSE;
		return (TRUE);
	}
	if (((str[var->i] != '<' && str[var->i] != '>' && str[var->i] != ' ' \
	&& str[var->i] != '|' && str[var->i] != '\'' && str[var->i] != '"') \
	&& !var->qutrg && var->rdrtrg))
	{
		var->j++;
		return (TRUE);
	}
	return (FALSE);
}

void	init_nordr_vars(t_var *var, char *str, int mode)
{
	var->rdrtrg = FALSE;
	var->qutrg = FALSE;
	var->len = ft_strlen(str);
	var->i = -1;
	var->j = 0;
	if (mode == 1)
	{
		var->size = count_size_without_redir(str);
		var->nordr = ft_calloc((var->size + 1), sizeof(char));
	}
}

int	count_size_without_redir(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_nordr_vars(&var, str, 0);
	while (++var.i < var.len && str[var.i])
	{
		check_quota(&var, str);
		check_rdrc(&var, str);
		check_pipe(&var, str, 0);
		if (continue_count(&var, str))
			continue ;
		var.j++;
	}
	return (var.j);
}

char	*conv_redir2spcs(char *str)
{
	t_var	var;

	var = (t_var){0};
	init_nordr_vars(&var, str, 1);
	while (++var.i < var.len && str[var.i])
	{
		check_quotation(&var, str);
		check_rdr(&var, str);
		check_pipe(&var, str, 1);
		if (continue_conv(&var, str))
			continue ;
		if (!var.rdrtrg)
			var.nordr[var.j++] = str[var.i];
		else if (str[var.i] != ' ' && var.rdrtrg)
			var.nordr[var.j++] = ' ';
	}
	if (var.nordr || var.nordr[var.j])
		var.nordr[var.j] = '\0';
	free_set_null(str);
	return (var.nordr);
}
