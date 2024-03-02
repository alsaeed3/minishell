/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dlr_sgn2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:10:29 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/17 18:00:06 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static char	*ft_strdup_2(char *str)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	ret = ft_calloc(3, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len && str[i] != '$' && str[i])
		i++;
	j = 0;
	while (j < 2 && i < len && str[i])
		ret[j++] = str[i++];
	ret[i] = '\0';
	return (ret);
}

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
	else if (*c >= '1' && *c <= '9')
	{
		tmp = ft_strdup_2(*input);
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
