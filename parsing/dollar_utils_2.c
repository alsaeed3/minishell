/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:09 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/09 10:57:54 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	dollar_heredoc_deli(char *str, t_var *var)
{
	if (var->i < var->len - 1 && (str[var->i] == '<' \
	&& str[var->i + 1] == '<') && !var->squtrg && !var->dqutrg && !var->rdrtrg)
		var->rdrtrg = TRUE;
	else if (var->i < var->len - 1 && (str[var->i] == '<' \
	&& str[var->i + 1] == '<') && !var->squtrg && !var->dqutrg && var->rdrtrg)
		var->rdrtrg = FALSE;
}

t_bool	exp_dlr_cnt_1(t_var *var, char *str)
{
	if ((str[var->i] == '\'' || str[var->i] == '"') \
	&& !var->squtrg && !var->dqutrg)
	{
		var->size++;
		var->i++;
		if (str[var->i] == '\'' && !var->squtrg && !var->dqutrg)
			var->squtrg = TRUE;
		else if (str[var->i] == '"' && !var->dqutrg && !var->squtrg)
			var->dqutrg = TRUE;
	}
	if (var->i < var->len - 1 && (str[var->i] == '<' && str[var->i + 1] == '<') \
	&& !var->squtrg && !var->dqutrg && !var->rdrtrg)
		var->rdrtrg = TRUE;
	else if (var->i < var->len - 1 && (str[var->i] == '<' \
	&& str[var->i + 1] == '<') && !var->squtrg && !var->dqutrg && var->rdrtrg)
	{
		var->rdrtrg = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

t_env	*ft_env_last(t_env *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	init_dollar_vars(t_var *var, char *str, t_env *env_lst, int mode)
{
	var->envalu = NULL;
	var->len = ft_strlen(str);
	var->rdrtrg = FALSE;
	var->squtrg = FALSE;
	var->dqutrg = FALSE;
	var->dlrtrg = FALSE;
	var->i = -1;
	var->j = 0;
	var->k = 0;
	var->size = 0;
	if (mode == 1)
		var->expsize = expand_dollar_count(str, env_lst);
}

void	init_del_exspc(t_var *var, char *str, int mode)
{
	var->len = 0;
	var->len = ft_strlen(str);
	var->i = -1;
	var->j = 0;
	var->size = 0;
	if (str[0] == ' ')
		jump_over_spaces(str, &var->i);
	var->qutrg = FALSE;
	if (mode == 1)
	{
		var->size = size_without_spcs(str);
		var->ret = ft_calloc(var->size + 1, sizeof(char));
	}
}
