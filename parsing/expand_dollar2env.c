/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar2env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:17:54 by alsaeed           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/13 21:29:41 by alsaeed          ###   ########.fr       */
=======
/*   Updated: 2024/02/19 16:30:06 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

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
			free_set_null((void **)&var->env);
	}
}

int	expand_dollar_count(char *str, t_env *env_lst)
{
	t_var	var;

	var = (t_var){0};
	init_dollar_vars(&var, str, env_lst, 0);
	while (++var.i < var.len && str[var.i])
	{
		if (((str[var.i] == '"' && str[var.i + 1] == '"') \
		|| (str[var.i] == '\'' && str[var.i + 1] == '\'')) \
		&& !var.qutrg)
		{
			var.size += 2;
			var.i++;
			continue ;
		}
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
	t_var	var;

	var = (t_var){0};
	init_dollar_vars(&var, str, env_lst, 1);
	var.ret = ft_calloc(var.expsize + 1, sizeof(char));
	if (!var.ret)
		return (NULL);
	while (++var.i < var.len && str[var.i])
	{
<<<<<<< HEAD
		if ((str[var.i] == '"' && str[var.i + 1] == '"') \
		|| (str[var.i] == '\'' && str[var.i + 1] == '\''))
		{
			var.i++;
			continue;
		}
		sd_quote_trg(&var, str);
=======
		if (cons_quot_dollar(&var, str))
			continue ;
>>>>>>> main
		rdr_trigger(&var, str);
		is_dollar(&var, str);
		expand_dollar(&var, str, env_lst);
		if (str[var.i] == '$' && ((str[var.i + 1] >= 65 \
		&& str[var.i + 1] <= 90) || (str[var.i + 1] >= 97 \
		&& str[var.i + 1] <= 122)) && !var.dlrtrg && !var.squtrg && !var.rdrtrg)
			var.dlrtrg = TRUE;
		else if (var.j <= var.expsize && str[var.i] \
		&& (!var.dlrtrg || str[var.i] != '$'))
			var.ret[var.j++] = str[var.i];
	}
	var.ret[var.j] = '\0';
	free_set_null((void **)&str);
	return (var.ret);
}
