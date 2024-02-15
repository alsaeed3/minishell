/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dlr_sgn2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:10:29 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/15 14:09:46 by alsaeed          ###   ########.fr       */
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
		free_set_null((void **)&tmp);
	}
	else if (*c == '0')
		*input = ft_strreplace(*input, "$0", "minishell");
	else if (ft_isalpha(*c) || ft_isdigit(*c) || *c == '_' || *c == '*')
	{
		tmp = ft_strjoin("$", c);
		*input = ft_strreplace(*input, tmp, "");
		free_set_null((void **)&tmp);
	}
}

void	expand_dolar_sign(char **inputs, t_parse *data)
{
	size_t	i;
	size_t	j;
	char	c;

	if (!inputs || !*inputs)
		return ;
	i = -1;
	while (++i < (size_t)ft_array_size(inputs))
	{
		j = -1;
		while (++j < ft_strlen(inputs[i]))
		{
			if (inputs[i][j] == '$')
			{
				c = inputs[i][j + 1];
				inside_loop(&inputs[i], &c, data);
				j++;
			}
		}
	}
}
