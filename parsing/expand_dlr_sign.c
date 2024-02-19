/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dlr_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:30:27 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/19 19:22:07 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

char	*expand_dollar_2(char *variable, t_dlr *dlr, t_parse *data)
{
	if (variable[0] == '?')
		return (dlr->i++, ft_itoa(data->exit_status));
	else if (variable[0] == '0')
		return (dlr->i++, ft_strdup("minishell"));
	else if (variable[0] == '#')
		return (dlr->i++, ft_strdup("0"));
	else if (variable[0] == '$')
		return (dlr->i++, ft_itoa(getpid()));
	else if ((variable[0] >= '1' && variable[0] <= '9') \
	|| ft_isalpha(variable[0]) || variable[0] == '*' \
	|| variable[0] == '@' || variable[0] == '!' \
	|| variable[0] == '-')
		return (dlr->i++, ft_strdup(""));
	return (NULL);
}

static t_bool	check_qt(char *str, t_dlr *dlr)
{
	if (str[dlr->i] == '\'')
	{
		dlr->in_single_quotes = !dlr->in_single_quotes;
		dlr->ret[dlr->j] = str[dlr->i];
		dlr->j++;
		return (TRUE);
	}
	else if (str[dlr->i] == '\"')
	{
		dlr->in_double_quotes = !dlr->in_double_quotes;
		dlr->ret[dlr->j++] = str[dlr->i];
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	expand_dlr(char *str, t_dlr *dlr, t_parse *data)
{
	if (str[dlr->i] == '$')
	{
		if (dlr->in_single_quotes)
			dlr->ret[dlr->j++] = str[dlr->i];
		else
		{
			dlr->expanded = expand_dollar_2(str + dlr->i + 1, dlr, data);
			if (dlr->expanded)
			{
				ft_strcpy(dlr->ret + dlr->j, dlr->expanded);
				dlr->j += ft_strlen(dlr->expanded);
				free_set_null((void **)&dlr->expanded);
			}
			else
				dlr->ret[dlr->j++] = str[dlr->i];
		}
		return (TRUE);
	}
	return (FALSE);
}

char	*expand_dollar_sign(char *str, t_parse *data)
{
	t_dlr	dlr;

	dlr = (t_dlr){0};
	dlr.ret = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dlr.ret)
		return (NULL);
	dlr.i = -1;
	while (++dlr.i < (int)ft_strlen(str))
	{
		if (!(check_qt(str, &dlr)))
			if (!(expand_dlr(str, &dlr, data)))
				dlr.ret[dlr.j++] = str[dlr.i];
	}
	free_set_null((void **)&str);
	if (dlr.ret && dlr.j < (int)ft_strlen(str) && dlr.ret[dlr.j])
		dlr.ret[dlr.j] = '\0';
	return (dlr.ret);
}
