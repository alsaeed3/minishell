/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:51:21 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/20 17:53:22 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

int	var_index(char *name, t_parse *data)
{
	int		y;
	int		x;

	x = 0;
	if (!data->env)
		return (-1);
	while (data->env[x])
	{
		y = 0;
		while (data->env[x][y] && data->env[x][y] == name[y]
		&& name[y] != '\0' && name[y] != '=' && name[y] != '+' &&
		data->env[x][y] != '\0' && data->env[x][y] != '=')
			y++;
		if ((data->env[x][y] == '\0' || data->env[x][y] == '=') &&
		(name[y] == '\0' || name[y] == '=' || name[y] == '+'))
			return (x);
		x++;
	}
	return (-1);
}

void	replace_var(char *new_var, t_parse *data, int index)
{
	char	*old_var;

	if (index < 0)
		return ;
	if (ft_strchr(new_var, '+'))
	{
		if (ft_strchr(data->env[index], '='))
		{
			old_var = ft_strjoin(data->env[index], ft_strchr(new_var, '=') + 1);
			free_set_null((void **)&data->env[index]);
			data->env[index] = old_var;
		}
		else
		{
			old_var = ft_strjoin(data->env[index], "=");
			free_set_null((void **)&data->env[index]);
			data->env[index] = ft_strjoin(old_var, ft_strchr(new_var, '=') + 1);
			free_set_null((void **)&old_var);
		}
	}
	else
	{
		free_set_null((void **)&data->env[index]);
		data->env[index] = ft_strdup(new_var);
	}
}

char	**export_env(char **old_env, char *export)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (envlen(old_env) + 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	free_env(old_env);
	new_env[i] = ft_strdup(export);
	i++;
	new_env[i] = NULL;
	return (new_env);
}

void	export_alone(t_parse *data)
{
	int		i;
	int		j;
	char	**temp_env;
	char	*swap;

	i = 0;
	if (!data->env || !data->env[0])
		return ;
	temp_env = dup_env(data->env);
	while (temp_env[i + 1])
	{
		j = i + 1;
		if (ft_strcmp1(temp_env[i], temp_env[j]) > 0)
		{
			swap = temp_env[j];
			temp_env[j] = temp_env[i];
			temp_env[i] = swap;
			i = 0;
		}
		else
			i++;
	}
	print_export(temp_env);
	free_env(temp_env);
}

int	handle_export(char **inputs, t_parse *data, int i)
{
	int	index;

	if (!inputs[i])
		export_alone(data);
	while (inputs[i])
	{
		index = var_index(inputs[i], data);
		if (index >= 0 && check_export(inputs[i]))
			replace_var(inputs[i], data, index);
		else if (check_export(inputs[i]))
		{
			data->env = export_env(data->env, inputs[i]);
			if (!data->env)
				return (1);
		}
		else
		{
			ft_error("export: not a valid identifier");
			return (1);
		}
		i++;
	}
	return (0);
}
