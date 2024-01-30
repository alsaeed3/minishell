/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:26:09 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/30 22:03:42 by alsaeed          ###   ########.fr       */
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
		var->rdrtrg = FALSE;
	if (var->i < var->len - 2 && str[var->i] == '$' && !(str[var->i + 1] >= 65 \
	&& str[var->i + 1] <= 90) && !(str[var->i + 1] >= 97 \
	&& str[var->i + 1] <= 122) && !var->squtrg)
	{
		var->i += 2;
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
