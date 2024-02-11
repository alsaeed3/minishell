/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dlr_sgn2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:10:29 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/11 16:54:53 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

void	inside_loop(char **input, char *c, t_parse *data)
{
	char	*tmp;

	tmp = NULL;
	if (*c == '?')
	{
		tmp = ft_itoa(data->exit_status);
		*input = ft_strreplace(*input, "$?", tmp);
		free_set_null(tmp);
	}
	else if (*c == '0')
		*input = ft_strreplace(*input, "$0", "minishell");
	else if (ft_isalpha(*c) || ft_isdigit(*c) || *c == '_' || *c == '*')
	{
		tmp = ft_strjoin("$", c);
		*input = ft_strreplace(*input, tmp, "");
		free_set_null(tmp);
	}
}

void	expand_dolar_sign(char **inputs, t_parse *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (inputs[i])
	{
		j = 0;
		while (inputs[i][j])
		{
			if (inputs[i][j] == '$')
			{
				c = inputs[i][j + 1];
				inside_loop(&inputs[i], &c, data);
				j++;
			}
			j++;
		}
		i++;
	}
}
