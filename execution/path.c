/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:13:53 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/28 14:54:33 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

char	**gen_paths(int index, t_parse *data, char *input)
{
	char	*str;
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	str = ft_strdup(&data->env[index][5]);
	paths = ft_split(str, ':');
	free(str);
	while (paths[i])
	{
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(temp);
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], input);
		free(temp);
		i++;
	}
	return (paths);
}

int	check_exec_path(char **inputs, t_parse *data)
{
	int			i;
	int			index;
	char		**paths;
	struct stat	statounet;

	statounet.st_mode = 0;
	i = 0;
	index = var_index("PATH=", data);
	if (var_index("PATH=", data) == -1)
		return (0);
	index = var_index("PATH=", data);
	paths = gen_paths(index, data, inputs[0]);
	while (paths[i])
	{
		stat(paths[i], &statounet);
		if ((statounet.st_mode & S_IXUSR) && !(statounet.st_mode & S_IFDIR))
		{
			free_env(paths);
			return (1);
		}
		i++;
	}
	free_env(paths);
	return (0);
}
