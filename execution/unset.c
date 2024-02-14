/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:23:49 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/14 20:57:07 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

char	**unset_env(char **old_env, int index)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (envlen(old_env) - 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (old_env[i])
	{
		if (i != index)
		{
			new_env[j] = ft_strdup(old_env[i]);
			j++;
		}
		i++;
	}
	free_env(old_env);
	i--;
	new_env[i] = NULL;
	return (new_env);
}

int	handle_unset(char **inputs, t_parse *data)
{
	int	i;
	int	index;

	i = 1;
	index = 0;
	while (inputs[i])
	{
		if (check_export(inputs[i]))
		{
			index = var_index(inputs[i], data);
			if (index >= 0)
				data->env = unset_env(data->env, index);
			i++;
		}
		else
		{
			ft_error("unset: invalid identifier");
			data->exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
