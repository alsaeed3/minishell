/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:23:29 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/09 10:52:05 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	exp_dlr_cnt_2(t_var *var, char *str)
{
	if (str[var->i] == '\'' && var->squtrg && !var->dqutrg)
	{
		var->size++;
		var->i++;
		var->squtrg = FALSE;
	}
	else if (str[var->i] == '"' && var->dqutrg && !var->squtrg)
	{
		var->size++;
		var->i++;
		var->dqutrg = FALSE;
	}
	if (str[var->i] == '$' && ((str[var->i + 1] >= 65 \
	&& str[var->i + 1] <= 90) || (str[var->i + 1] >= 97 \
	&& str[var->i + 1] <= 122)) && !var->dlrtrg && !var->squtrg && !var->rdrtrg)
		var->dlrtrg = TRUE;
	else if (str[var->i] && (!var->dlrtrg || str[var->i] != '$'))
		var->size++;
}

void	rdr_trigger(t_var *var, char *str)
{
	if (var->i < var->len - 1 && ((str[var->i] == '<' && str[var->i + 1] != '<' \
	&& (var->i == 0 || str[var->i - 1] != '<')) || (str[var->i] == '>' \
	&& str[var->i + 1] != '>' && (var->i == 0 || str[var->i - 1] != '>'))) \
	&& !var->squtrg && !var->dqutrg)
		var->rdrtrg = TRUE;
	else if (var->i < var->len - 1 && ((str[var->i] == '<' \
	&& str[var->i + 1] == '<') || (str[var->i] == '>' \
	&& str[var->i + 1] == '>')) && !var->squtrg && !var->dqutrg)
		var->rdrtrg = TRUE;
	else if (var->i < var->len - 1 && ((str[var->i] == '<' \
	&& str[var->i + 1] != '<' && (var->i == 0 || str[var->i - 1] != '<')) \
	|| (str[var->i] == '>' && str[var->i + 1] != '>' && (var->i == 0 \
	|| str[var->i - 1] != '>'))) && (var->squtrg || var->dqutrg))
		var->rdrtrg = FALSE;
	else if (var->i < var->len - 1 && ((str[var->i] == '<' \
	&& str[var->i + 1] == '<') || (str[var->i] == '>' \
	&& str[var->i + 1] == '>')) && (var->squtrg || var->dqutrg))
		var->rdrtrg = FALSE;
}

void	is_dollar(t_var *var, char *str)
{
	if (str[var->i] == '$' && ((str[var->i + 1] >= 65 \
	&& str[var->i + 1] <= 90) || (str[var->i + 1] >= 97 \
	&& str[var->i + 1] <= 122)) && !var->squtrg && !var->rdrtrg)
		var->dlrtrg = TRUE;
}

void	expand_dollar(t_var *var, char *str, t_env *env_lst)
{
	if (var->dlrtrg && ((str[var->i] >= 65 && str[var->i] <= 90) \
	|| (str[var->i] >= 97 && str[var->i] <= 122)))
	{
		var->env = ft_calloc(find_env_size(str, var->i) + 1, sizeof(char));
		var->k = 0;
		var->env[var->k++] = str[var->i];
		while (++var->i < var->len && ((str[var->i] >= 65 && str[var->i] <= 90) \
		|| (str[var->i] >= 97 && str[var->i] <= 122) \
		|| (str[var->i] >= 48 && str[var->i] <= 57)))
			var->env[var->k++] = str[var->i];
		var->env[var->k] = '\0';
		var->dlrtrg = FALSE;
		if (ft_getenv(var->env, env_lst))
		{
			var->k = 0;
			var->envalu = ft_getenv(var->env, env_lst);
			while (var->j < var->expsize && var->envalu[var->k])
				var->ret[var->j++] = var->envalu[var->k++];
		}
		if (var->env)
			free_set_null(var->env);
	}
}

void	sd_quote_trg(t_var *var, char *str)
{
	if (str[var->i] == '\'' && !var->squtrg && !var->dqutrg)
		var->squtrg = TRUE;
	else if (str[var->i] == '"' && !var->dqutrg && !var->squtrg)
		var->dqutrg = TRUE;
	else if (str[var->i] == '\'' && var->squtrg && !var->dqutrg)
		var->squtrg = FALSE;
	else if (str[var->i] == '"' && var->dqutrg && !var->squtrg)
		var->dqutrg = FALSE;
}
