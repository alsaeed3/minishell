/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:23:49 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/20 11:10:58 by habu-zua         ###   ########.fr       */
=======
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:23:49 by habu-zua          #+#    #+#             */
/*   Updated: 2024/02/15 15:11:01 by alsaeed          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

<<<<<<< HEAD

=======
>>>>>>> main
char	**unset_env(char **old_env, int index)
{
	int		i;
	int		j;
	char	**new_env;

<<<<<<< HEAD
	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (envlen(old_env) - 1));
	if (!new_env)
		exit(EXIT_FAILURE);
=======
	if (!old_env)
		return (NULL);
	new_env = malloc(sizeof(char *) * (envlen(old_env) - 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
>>>>>>> main
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

<<<<<<< HEAD
void	handle_unset(char **inputs, t_parse *data)
{
	int	i;
	int	index;

	i = 1;
	while (inputs[i])
=======
int	handle_unset(char **inputs, t_parse *data)
{
	int	i;
	int	index;
	int	len;

	i = 1;
	len = ft_array_size(inputs);
	while (i < len && inputs[i])
>>>>>>> main
	{
		if (check_export(inputs[i]))
		{
			index = var_index(inputs[i], data);
<<<<<<< HEAD
			if (index > 0)
=======
			if (index >= 0)
>>>>>>> main
				data->env = unset_env(data->env, index);
			i++;
		}
		else
<<<<<<< HEAD
			return (error_sentence("unset: invalid identifier\n", 1));
	}
=======
		{
			ft_error("unset: invalid identifier");
			data->exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
>>>>>>> main
}
