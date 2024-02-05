/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar2env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:17:54 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/05 16:53:24 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	find_env_size(char *str, int i)
{
	int	len;
	int	size;

	len = ft_strlen(str);
	size = 0;
	if (str[i] == '$')
		i++;
	while (i < len && ((str[i] >= 65 && str[i] <= 90) \
	|| (str[i] >= 97 && str[i] <= 122) \
	|| (str[i] >= 48 && str[i] <= 57)))
	{
		size++;
		i++;
	}
	return (size);
}

void	find_exp_size(t_var *var, char *str, t_env *env_lst)
{
	if (var->dlrtrg && ((str[var->i] >= 65 && str[var->i] <= 90) \
	|| (str[var->i] >= 97 && str[var->i] <= 122)))
	{
		var->env = ft_calloc(find_env_size(str, var->i) + 1, sizeof(char));
		if (!var->env)
			return ;
		var->j = 0;
		var->env[var->j++] = str[var->i];
		while (++var->i < var->len && ((str[var->i] >= 65 && str[var->i] <= 90) \
		|| (str[var->i] >= 97 && str[var->i] <= 122) \
		|| (str[var->i] >= 48 && str[var->i] <= 57)))
			var->env[var->j++] = str[var->i];
		var->env[var->j] = '\0';
		var->dlrtrg = FALSE;
		if (ft_getenv(var->env, env_lst))
			var->size += ft_strlen(ft_getenv(var->env, env_lst));
		if (var->env)
		{
			free (var->env);
			var->env = NULL;
		}
	}
}

int	expand_dollar_count(char *str, t_env *env_lst)
{
	t_var	var = {0};

	init_dollar_vars(&var, str, env_lst, 0);
	while (++var.i < var.len && str[var.i])
	{
		if (!exp_dlr_cnt_1(&var, str))
		{
			if (str[var.i] == '$' && ((str[var.i + 1] >= 65 \
			&& str[var.i + 1] <= 90) || (str[var.i + 1] >= 97 \
			&& str[var.i + 1] <= 122)) && !var.squtrg && !var.rdrtrg)
				var.dlrtrg = TRUE;
		}
		find_exp_size(&var, str, env_lst);
		exp_dlr_cnt_2(&var, str);
	}
	return (var.size);
}

char	*expand_dollar_string(char *str, t_env *env_lst)
{
	t_var	var = {0};

	init_dollar_vars(&var, str, env_lst, 1);
	var.ret = ft_calloc(var.expsize + 1, sizeof(char));
	if (!var.ret)
		return (NULL);
	while (++var.i < var.len && str[var.i])
	{
		sd_quote_trg(&var, str);
		rdr_trigger(&var, str);
		is_dollar(&var, str);
		expand_dollar(&var, str, env_lst);
		if (str[var.i] == '$' && ((str[var.i + 1] >= 65 \
		&& str[var.i + 1] <= 90) || (str[var.i + 1] >= 97 \
		&& str[var.i + 1] <= 122)) && !var.dlrtrg \
		&& !var.squtrg && !var.rdrtrg)
			var.dlrtrg = TRUE;
		else if (str[var.i] && (!var.dlrtrg || str[var.i] != '$'))
			var.ret[var.j++] = str[var.i];
	}
	var.ret[var.j] = '\0';
	free (str);
	str = NULL;
	return (var.ret);
}
